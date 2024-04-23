/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <cmath>

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
    
private:
    //==============================================================================
    
    juce::dsp::LinkwitzRileyFilter<float> lowPassFilter, highPassFilter;

    
    double currentFs{44100.f};
    
    float curInSample{0.f}, curOutSample{0.f};
    float prevInSample{0.f}, prevOutSample{0.f};
    
    float curInTrebleSample{0.f}, curOutTrebleSample{0.f};
    float prevInTrebleSample{0.f}, prevOutTrebleSample{0.f};
    
    float getLFO() const;
    float getLFO(bool) const;
    
    void updateCutoff(float);
    void updateAmplitude(float);
    void updateRotationSpeed(float);
    
    struct Modulator
    {
        float freq{0.f};
        float amplitide{0.f};
        float bias{0.f};
        double fs{44100.f};
        
        float getNextValue()
        {
            n++;
            auto nextValue = std::sin(2*M_PI*freq*n / fs );
            //nextValue = 0.20 * nextValue + 0.8;
            nextValue = amplitide * nextValue + bias;
            return nextValue;
        }
        
        void changeFreq(float newFreq)
        {
            reset();
            freq = newFreq;
        }
        
        void changeAmplitudeBias(float newAmp, float newBias)
        {
            reset();
            amplitide = newAmp;
            bias = newBias;
        }
        
        void reset()
        {
            n = -1;
        }
    private:
        int n = -1;
        
    };
    
    struct ParamId
    {
        static const inline juce::String cutOff{"cutoff"};
        static const inline juce::String balance{"balance"};
        static const inline juce::String slowSpeed{"slowSpeed"};
        static const inline juce::String amplitude{"amplitude"};
        static const inline juce::String bassFilterOrder{"bassFilterOrder"};
        static const inline juce::String trebleFilterOrder{"trebleFilterOrder"};
    };
    
    Modulator bassAmpModulator, trebleAmpModulator;
    Modulator bassFreqModulator, trebleFreqModulator;
    
    juce::dsp::DryWetMixer<float> dwMixer{0};
    
    const float slowSpeed{2.f};
    const float fastSpeed{6.f};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeslieSpeakerPluginAudioProcessor)
};
