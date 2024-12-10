/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

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
     * Variables used in the signal processing block.
     * These members handle audio processing tasks.
     */
    float curInSample{0.f}, curOutSample{0.f};
    float prevInSample{0.f}, prevOutSample{0.f};
    
    float curInTrebleSample{0.f}, curOutTrebleSample{0.f};
    float prevInTrebleSample{0.f}, prevOutTrebleSample{0.f};
    
    /**
     * Modulation frequencies corresponding to slow and fast rotation speed.
     */
    const float slowModulationFreq{2.f};
    const float fastModulationFreq{6.f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeslieSpeakerPluginAudioProcessor)
};
