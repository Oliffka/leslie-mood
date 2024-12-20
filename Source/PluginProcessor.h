/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#include <vector>
#include <JuceHeader.h>

//==============================================================================
/**
*/
class LeslieSpeakerPluginAudioProcessor : public juce::AudioProcessor,
                                          public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    LeslieSpeakerPluginAudioProcessor();
    ~LeslieSpeakerPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    
    juce::AudioProcessorValueTreeState tree;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameters();
     
    /**
     * A crossover implementation that splits the input signal's frequency range
     * into two parts: treble and bass. The two bands are then processed separately
     * using specific parameters. Finally, a DryWetMixer is employed to blend the
     * processed signals in the desired proportion.
     */
    juce::dsp::LinkwitzRileyFilter<float> lowPassFilter, highPassFilter;
    juce::dsp::DryWetMixer<float> dwMixer{0};
    
    /**
     * This structure is used to represent modulators. The modulator outputs values over time,
     * calculated based on its frequency, scale, and bias parameters.
     * These values are updated every time a new sample is requested.
     *
     * @param freq The frequency of the modulator in Hertz (Hz) that determines the rotation speed.
     * In a Leslie speaker simulation, slow and fast rotation speeds correspond to
     * frequencies of  2 Hz and 6 Hz, respectively  (in the current implementation).
     *
     * @param scale The scaling factor for the modulator's amplitude.
     *   This adjusts the range of modulation by scaling the output sinusoid.
     *
     * @param bias The bias added to the scaled modulating value.
     *   This shifts the output's base, allowing the modulator's to be in any desired range.
     *
     *  Thus, final formula used to generate modulating values is:
     *  m(n) = Scale * m_0(n) + Bias, where m_0(n) is the base sine wave output that fluctuates in [-1, 1].
     *
     * @param fs  The sampling frequency of an audio signal in Hertz (Hz).
     */
    struct Modulator
    {
        float freq{0.f};
        float scale{0.f};
        float bias{0.f};
        double fs{44100.f};
        const float pi_num = juce::MathConstants<float>::pi;
        
        /**
         * Computes and returns the next value of the modulator.
         *
         * @return The next modulating value, adjusted by scale and bias to ensure
         *         it lies within the desired range: [bias - scale, bias + scale].
         */
        float getNextValue()
        {
            n++;
            auto nextValue = std::sin(2*pi_num*freq*n / fs );
            nextValue = scale * nextValue + bias;
            return nextValue;
        }
        
        void changeFreq(float newFreq)
        {
            reset();
            freq = newFreq;
        }
        
        void changeScaleBias(float newScale, float newBias)
        {
            reset();
            scale = newScale;
            bias = newBias;
        }
        
        void reset()
        {
            n = -1;
        }
    private:
        int n = -1;
        
    };
    
    /**
     * Amplitude and frequency modulators for treble and bass frequency ranges.
     */
    Modulator bassAmpModulator, trebleAmpModulator;
    Modulator bassFreqModulator, trebleFreqModulator;
    
    /**
     * User-configurable parameters for the Leslie Speaker simulation.
     * These parameters define key aspects of the simulation, such as cutoff frequency,
     * rotation speed, and filter characteristics.
     */
    struct ParamId
    {
        static const inline juce::String cutOff{"cutoff"};
        static const inline juce::String balance{"balance"};
        static const inline juce::String slowSpeed{"slowSpeed"};
        static const inline juce::String amplitude{"amplitude"};
        static const inline juce::String bassFilterOrder{"bassFilterOrder"};
        static const inline juce::String trebleFilterOrder{"trebleFilterOrder"};
    };
    
    /**
     * Setter and getter methods
     */
    float getModulationFrequency() const;
    float getModulationFrequency(bool) const;
    
    void updateCutoff(float);
    void updateAmplitude(float);
    void updateRotationSpeed(float);
    
    /**
     * This structure stores the delay line values required to implement a cascade of several all-pass filters.
     * For each filter in the cascade, we use the difference equation:
     * y(n) = m(n)x(n) + x(n−1) − m(n)y(n−1),
     * so we need to keep track of the previous input (x(n-1)) and previous output (y(n-1)) for
     * each all-pass filter in the cascade. This structure provides separate delay line states for both the treble
     * and bass processing paths.
     *
     * The maximum order of the SDF filter  (number of all-pass filters in cascade) is specified as `maxOrder`.
     */
    struct DelayLineState
    {
    public:
        /**
         * Constructor: Initializes the delay line state for the specified maximum order of a filter.
         *
         * @param max_order The maximum number of all-pass filters in the cascade.
         */
        DelayLineState(int max_order)
        {
            Init(max_order);
        }
        
        // Vectors to store delay line states for treble and bass processing paths
        std::vector<float> trebleDelayLineIn;
        std::vector<float> trebleDelayLineOut;
        std::vector<float> bassDelayLineIn;
        std::vector<float> bassDelayLineOut;
        int maxOrder;
        
    private:
        void Init(int max_order)
        {
            maxOrder = max_order;
            
            // Reserve memory for delay lines to avoid frequent allocations
            trebleDelayLineIn.reserve(max_order);
            trebleDelayLineOut.reserve(max_order);
            bassDelayLineIn.reserve(max_order);
            bassDelayLineOut.reserve(max_order);
            
            // Initialize all delay line values to 0.0
            for(auto i = 0; i < max_order; i++ )
            {
                trebleDelayLineIn.push_back(0.f);
                bassDelayLineIn.push_back(0.f);
                trebleDelayLineOut.push_back(0.f);
                bassDelayLineOut.push_back(0.f);
            }
        }
    };
    std::vector<DelayLineState> delayLines;
    
    /**
     * Modulation frequencies corresponding to slow and fast rotation speed.
     */
    const float slowModulationFreq{2.f};
    const float fastModulationFreq{6.f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeslieSpeakerPluginAudioProcessor)
};
