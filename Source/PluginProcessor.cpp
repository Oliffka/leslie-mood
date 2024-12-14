/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LeslieSpeakerPluginAudioProcessor::LeslieSpeakerPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), tree(*this, nullptr, "Parameters", createParameters())
#endif
{
    tree.addParameterListener (ParamId::cutOff, this);
    tree.addParameterListener (ParamId::slowSpeed, this);
    tree.addParameterListener (ParamId::balance, this);
    tree.addParameterListener (ParamId::amplitude, this);
    tree.addParameterListener (ParamId::bassFilterOrder, this);
    tree.addParameterListener (ParamId::trebleFilterOrder, this);
    
    lowPassFilter.setType(juce::dsp::LinkwitzRileyFilterType::lowpass);
    highPassFilter.setType(juce::dsp::LinkwitzRileyFilterType::highpass);
}

LeslieSpeakerPluginAudioProcessor::~LeslieSpeakerPluginAudioProcessor()
{
}

//==============================================================================
const juce::String LeslieSpeakerPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LeslieSpeakerPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LeslieSpeakerPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LeslieSpeakerPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LeslieSpeakerPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LeslieSpeakerPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LeslieSpeakerPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LeslieSpeakerPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String LeslieSpeakerPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void LeslieSpeakerPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void LeslieSpeakerPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Configure the DSP processing specification
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;                  // Set the sample rate
    spec.maximumBlockSize = samplesPerBlock;       // Set the block size
    spec.numChannels = getTotalNumOutputChannels();// Set the number of output channels
    
    // Initialize the low-pass and high-pass filters
    lowPassFilter.prepare(spec);
    lowPassFilter.reset();                         // Reset filter state
    
    highPassFilter.prepare(spec);
    highPassFilter.reset();                        // Reset filter state
    
    // Prepare and configure the dry/wet mixer
    dwMixer.prepare(spec);
    dwMixer.setMixingRule(juce::dsp::DryWetMixingRule::balanced);
    
    // Retrieve and set the initial mix balance
    const float balance = *tree.getRawParameterValue(ParamId::balance);
    dwMixer.setWetMixProportion(balance);
    
    // Retrieve the initial cutoff frequency and update filters
    const float cutoff = *tree.getRawParameterValue(ParamId::cutOff);
    updateCutoff(cutoff);
    
    // Retrieve modulation frequency and update rotation speed
    const auto modFreq = getModulationFrequency();
    updateRotationSpeed(modFreq);
    
    // Set the sampling rate for amplitude and frequency modulators
    bassAmpModulator.fs = sampleRate;
    trebleAmpModulator.fs = sampleRate;
    bassFreqModulator.fs = sampleRate;
    trebleFreqModulator.fs = sampleRate;
    
    // Set the initial modulation amplitude
    const float amplitude = *tree.getRawParameterValue(ParamId::amplitude);
    const auto bottomLimit = 1 - amplitude;
    updateAmplitude(bottomLimit);
    
    // Configure modulation parameters for bass and treble frequencies
    // These values are derived from a research article that describes this method
    // and are chosen to create a pleasant sound effect.
    bassFreqModulator.scale = 0.04f;  // Scale for bass frequency modulation
    bassFreqModulator.bias = -0.92f;  // Bias for bass frequency modulation
    
    trebleFreqModulator.scale = 0.2f; // Scale for treble frequency modulation
    trebleFreqModulator.bias = -0.75f;// Bias for treble frequency modulation
    
    // Initialize delay lines for further dsp processing
    delayLines.clear();
    delayLines.reserve(getTotalNumInputChannels());
    const auto bassFilterMaxOrder = tree.getParameter(ParamId::bassFilterOrder)->getNormalisableRange().end;
    
    const auto trebleFilterMaxOrder = tree.getParameter(ParamId::trebleFilterOrder)->getNormalisableRange().end;
    
    const auto maxOrder = static_cast<int>(std::max(bassFilterMaxOrder, trebleFilterMaxOrder));
    
    for (auto i = 0; i < getTotalNumInputChannels(); ++i)
    {
        delayLines.push_back(DelayLineState{maxOrder});
    }
}

void LeslieSpeakerPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LeslieSpeakerPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// Initializes the parameters that the user can configure for the audio plugin
juce::AudioProcessorValueTreeState::ParameterLayout LeslieSpeakerPluginAudioProcessor::createParameters()
{
    // Vector to hold all the parameters
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // Parameter for the crossover cutoff frequency between bass and treble.
    // Default: 700 Hz, Range: 500 Hz to 1500 Hz.
    params.push_back(std::make_unique<juce::AudioParameterInt> (ParamId::cutOff, "crossover cutoff frequency", 500, 1500, 700));
    
    // Parameter for balancing bass and treble levels.
    // Values of 0 or 1 emphasize low-frequency (bass) or high-frequency (treble) components respectively.
    // Default: 0.5 (balanced), Range: 0.0 to 1.0.
    params.push_back(std::make_unique<juce::AudioParameterFloat> (ParamId::balance, "bass/treble balance", 0.f, 1.f, 0.5f));
    
    // Parameter for controlling the amplitude modulation depth.
    // Allows the user to set how strongly the amplitude varies over time.
    // Default: 0.2, Range: 0.0 to 1.0.
    params.push_back(std::make_unique<juce::AudioParameterFloat> (ParamId::amplitude, "amplitude modulation depth", 0.f, 1.f, 0.2f));
    
    // Parameter to define the order of the bass SDF filter.
    // Default: 3, Range: 1 to 5.
    params.push_back(std::make_unique<juce::AudioParameterInt> (ParamId::bassFilterOrder, "SDF filter's order for bass modulation", 1, 6, 3));
    
    // Parameter to define the order of the treble SDF filter.
    // Default: 4, Range: 1 to 5.
    params.push_back(std::make_unique<juce::AudioParameterInt> (ParamId::trebleFilterOrder, "SDF filter's order for treble modulation", 1, 6, 4));
    
    // Boolean parameter to toggle the rotation speed between slow and fast.
    // Default: true (slow speed).
    params.push_back(std::make_unique<juce::AudioParameterBool> (ParamId::slowSpeed, "rotation speed is slow", true));
    
    return { params.begin(), params.end() };
}

float LeslieSpeakerPluginAudioProcessor::getModulationFrequency() const
{
    bool slowSpeedParam = *tree.getRawParameterValue(ParamId::slowSpeed);
    return getModulationFrequency(slowSpeedParam);
}

float LeslieSpeakerPluginAudioProcessor::getModulationFrequency(bool slowSpeedParameter) const
{
    return slowSpeedParameter ? slowModulationFreq : fastModulationFreq;
}

// Updates the relevant parameters when their values change
void LeslieSpeakerPluginAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == ParamId::cutOff)
    {
        updateCutoff(newValue);
    }
    else if (parameterID == ParamId::slowSpeed)
    {
        updateRotationSpeed(getModulationFrequency(static_cast<int>(newValue) == 1));
    }
    else if (parameterID == ParamId::amplitude)
    {
        const auto bottomLimit = 1 - newValue;
        updateAmplitude(bottomLimit);
    }
    else if (parameterID == ParamId::balance)
    {
        dwMixer.setWetMixProportion(newValue);
    }
}

// Updates the cutoff frequency for both low-pass and high-pass filters
void LeslieSpeakerPluginAudioProcessor::updateCutoff(float newCutoff)
{
    lowPassFilter.setCutoffFrequency(newCutoff);
    highPassFilter.setCutoffFrequency(newCutoff);
}

// Adjusts the amplitude modulation scale and bias
void LeslieSpeakerPluginAudioProcessor::updateAmplitude(float bottomLimit)
{
    // This is done to guarantee the amplitude modulation range is [bottomLimit, 1]
    const auto scale = (1 - bottomLimit) / 2;
    const auto bias = bottomLimit + scale;
    
    bassAmpModulator.changeScaleBias(scale, bias);
    trebleAmpModulator.changeScaleBias(scale, bias);
}

// Adjusts the rotation speed for modulation frequency
void LeslieSpeakerPluginAudioProcessor::updateRotationSpeed(float newModFreq)
{
    // As the treble and bass motors are running at slightly different speed,
    // the treble modulator has 0.1 Hz higher frequency compared to bass modulator
    bassAmpModulator.changeFreq(newModFreq - 0.05f);
    bassFreqModulator.changeFreq(newModFreq - 0.05f);
    
    trebleAmpModulator.changeFreq(newModFreq + 0.05f);
    trebleFreqModulator.changeFreq(newModFreq + 0.05f);
}

void LeslieSpeakerPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    
    juce::dsp::AudioBlock<const float> inputBlock(buffer);
    
    juce::AudioBuffer<float> outBufferLP(inputBlock.getNumChannels(), inputBlock.getNumSamples());
    
    juce::AudioBuffer<float> outBufferHP(inputBlock.getNumChannels(), inputBlock.getNumSamples());
    
    juce::dsp::AudioBlock<float> outBlockLP(outBufferLP);
    juce::dsp::AudioBlock<float> outBlockHP(outBufferHP);
    
    auto contextLP = juce::dsp::ProcessContextNonReplacing<float>(inputBlock, outBlockLP);
    auto contextHP = juce::dsp::ProcessContextNonReplacing<float>(inputBlock, outBlockHP);
    
    lowPassFilter.process(contextLP);
    highPassFilter.process(contextHP);
    
    int filterOrderBass = *tree.getRawParameterValue(ParamId::bassFilterOrder);
    int filterOrderTreble = *tree.getRawParameterValue(ParamId::trebleFilterOrder);
    
    // Frequency modulation lambda function
    auto doFrequencyModulation = [](auto& delayLineIn, auto& delayLineOut, int filterOrder, float nextModValue, float inputSample) {
        
        // initialize current sample with input value
        float curSample = inputSample;
        
        // looping through number of all-pass filters in cascade
        for (int i = 0; i < filterOrder; i++) {
            // compute output value according to the difference equation:
            // y(n) = m(n)x(n) + x(n−1) − m(n)y(n−1),
            float outSample = nextModValue * curSample + delayLineIn[i] - nextModValue * delayLineOut[i];
            
            // update delay line state
            delayLineIn[i] = curSample;
            delayLineOut[i] = outSample;
            
            // now, output sample of the prev filter is an input sample for the next filter
            curSample = outSample;
        }
        return curSample;
    };
    
    for (int sample = 0; sample < outBlockLP.getNumSamples(); ++sample)
    {
        // get next modulating values
        auto bassModAmp = bassAmpModulator.getNextValue();
        auto trebleModAmp = trebleAmpModulator.getNextValue();
        
        auto bassModFreq = bassFreqModulator.getNextValue();
        auto trebleModFreq = trebleFreqModulator.getNextValue();
        
        // process each input channel separately
        for (int channel = 0; channel < outBlockLP.getNumChannels(); ++channel)
        {
            //Bass Amp + Frequency modulation
            auto curInBassSample = outBlockLP.getSample(channel, sample);
            
            auto curOutBassSample = doFrequencyModulation(
                        delayLines[channel].bassDelayLineIn,
                        delayLines[channel].bassDelayLineOut,
                        filterOrderBass,
                        bassModFreq,
                        curInBassSample) * bassModAmp;

            outBlockLP.setSample(channel, sample, curOutBassSample);
            
            //Treble Amp + Frequency modulation
            auto curInTrebleSample = outBlockHP.getSample(channel, sample);
            
            auto curOutTrebleSample = doFrequencyModulation(
                        delayLines[channel].trebleDelayLineIn,
                        delayLines[channel].trebleDelayLineOut,
                        filterOrderTreble,
                        trebleModFreq,
                        curInTrebleSample) * trebleModAmp;

            outBlockHP.setSample(channel, sample, curOutTrebleSample);
        }
    }
    
    // blend bass(outBlockLP) and treble(outBlockHP) paths in the required proportion
    // final output signal is stored in outBufferHP
    dwMixer.pushDrySamples(outBlockLP);
    dwMixer.mixWetSamples(outBlockHP);
    
    // copy processed signal(outBufferHP) to the buffer
    for (auto i = 0; i < totalNumInputChannels; ++i)
    {
        buffer.copyFrom(i,0, outBufferHP, i, 0, outBufferHP.getNumSamples());
    }
}

//==============================================================================
bool LeslieSpeakerPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* LeslieSpeakerPluginAudioProcessor::createEditor()
{
    return new LeslieSpeakerPluginAudioProcessorEditor (*this);
}

//==============================================================================
void LeslieSpeakerPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = tree.copyState();
    std::unique_ptr<juce::XmlElement> xml (state.createXml());
    copyXmlToBinary (*xml, destData);
}

void LeslieSpeakerPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName (tree.state.getType()))
            tree.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LeslieSpeakerPluginAudioProcessor();
}
