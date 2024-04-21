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
                       ), tree(*this, nullptr, "Parameters", createParameters()), 
lowPassFilter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 20000.0f, 0.1f)),
highPassFilter(juce::dsp::IIR::Coefficients<float>::makeHighPass(44100, 20000.0f, 0.1f))
#endif
{
    tree.addParameterListener (ParamId::cutOff, this);
    tree.addParameterListener (ParamId::slowSpeed, this);
    tree.addParameterListener (ParamId::balance, this);
    tree.addParameterListener (ParamId::amplitude, this);
    tree.addParameterListener (ParamId::stereo, this);
    tree.addParameterListener (ParamId::panpot, this);
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
    currentFs = sampleRate;
    
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    lowPassFilter.prepare(spec);
    lowPassFilter.reset();
    
    highPassFilter.prepare(spec);
    highPassFilter.reset();
    
    float modFreq = getLFO();
    //TODO::
    bassAmpModulator.freq = modFreq - 0.05;
    bassAmpModulator.amplitide = 0.2f;
    bassAmpModulator.bias = 0.8f;
    bassAmpModulator.fs = sampleRate;
    
    trebleAmpModulator.freq = modFreq + 0.05;
    trebleAmpModulator.amplitide = 0.2f;
    trebleAmpModulator.bias = 0.8f;
    trebleAmpModulator.fs = sampleRate;
    
    bassFreqModulator.freq = modFreq - 0.05;
    bassFreqModulator.amplitide = 0.04f;
    bassFreqModulator.bias = -0.92f;
    bassFreqModulator.fs = sampleRate;
    
    trebleFreqModulator.freq = modFreq + 0.05;
    trebleFreqModulator.amplitide = 0.2f;
    trebleFreqModulator.bias = -0.75f;
    trebleFreqModulator.fs = sampleRate;
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

juce::AudioProcessorValueTreeState::ParameterLayout LeslieSpeakerPluginAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (ParamId::cutOff, "crossover cutoff frequency", 500.f, 2000.f, 800.f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (ParamId::balance, "bass/treble balance", 0.f, 1.f, 0.5f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (ParamId::amplitude, "amplitude modulation", 0.f, 0.9f, 0.7f));
    
    params.push_back(std::make_unique<juce::AudioParameterFloat> (ParamId::panpot, "left/right channels balance", 0.f, 1.f, 0.5f));
    
    params.push_back(std::make_unique<juce::AudioParameterBool> (ParamId::slowSpeed, "rotation speed is slow", true));
    
    params.push_back(std::make_unique<juce::AudioParameterBool> (ParamId::stereo, "bass/treble stereo", false));
    
    return{ params.begin(), params.end() };
}

float LeslieSpeakerPluginAudioProcessor::getLFO() const
{
    bool slowSpeedParam = *tree.getRawParameterValue(ParamId::slowSpeed);
    return getLFO(slowSpeedParam);
}

float LeslieSpeakerPluginAudioProcessor::getLFO(bool slowSpeedParameter) const
{
    return slowSpeedParameter ? slowSpeed : fastSpeed;
}

void LeslieSpeakerPluginAudioProcessor::parameterChanged (const juce::String& parameterID, float newValue)
{
    if (parameterID == ParamId::cutOff)
    {
        float freq = newValue;
        float res = 0.1f;
        
        *lowPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(currentFs, freq, res);
        
        *highPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(currentFs, freq, res);
    }
    else if (parameterID == ParamId::slowSpeed)
    {
        int value = static_cast<int>(newValue);
        
        const auto lfo = getLFO(value == 1);
        
        bassAmpModulator.changeFreq(lfo - 0.05f);
        bassFreqModulator.changeFreq(lfo - 0.05f);
        
        trebleAmpModulator.changeFreq(lfo + 0.05f);
        trebleFreqModulator.changeFreq(lfo + 0.05f);
    }
    /*tree.addParameterListener ("cutoff", this);
    tree.addParameterListener ("slowSpeed", this);
    tree.addParameterListener ("balance", this);
    tree.addParameterListener ("amplitude", this);
    tree.addParameterListener ("stereo", this);
    tree.addParameterListener ("panpot", this);
    updateFilter();*/
}


void LeslieSpeakerPluginAudioProcessor::updateFilter()
{
    float freq = *tree.getRawParameterValue("cutoff");
    float res = 0.1f;
    
    *lowPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(currentFs, freq, res);
    
    *highPassFilter.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(currentFs, freq, res);
    
    const auto lfo = getLFO();
    
    bassAmpModulator.changeFreq(lfo - 0.05f);
    bassFreqModulator.changeFreq(lfo - 0.05f);
    
    trebleAmpModulator.changeFreq(lfo + 0.05f);
    trebleFreqModulator.changeFreq(lfo + 0.05f);
    
    bool stereoParam = *tree.getRawParameterValue("stereo");
    bool slowSpeedParam = *tree.getRawParameterValue("slowSpeed");
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
    
    //TODO:??
    //updateFilter();
    
    lowPassFilter.process(contextLP);
    highPassFilter.process(contextHP);
    
    //auto outBlock = context.getOutputBlock();

        //auto* channelData = outBlock.getChannelPointer(channel);
    for (int sample = 0; sample < outBlockLP.getNumSamples(); ++sample)
    {
        auto next_bass_value = bassAmpModulator.getNextValue();
        auto next_treble_value = trebleAmpModulator.getNextValue();
        
        for (int channel = 0; channel < outBlockLP.getNumChannels(); ++channel)
        {
            std::cout << "Next bass value: " << next_bass_value << std::endl;
            auto curSample = outBlockLP.getSample(channel, sample);
            //std::cout << "Current lp sample: " << curSample << std::endl;
            curSample *= next_bass_value;
            //std::cout << "Current lp sample after modulation: " << curSample << std::endl;
            outBlockLP.setSample(channel, sample, curSample);
            
            std::cout << "Next treble value: " << next_treble_value << std::endl;
            curSample = outBlockHP.getSample(channel, sample);
            //std::cout << "Current hp sample: " << curSample << std::endl;
            curSample *= next_treble_value;
            //std::cout << "Current hp sample after modulation: " << curSample << std::endl;
            outBlockHP.setSample(channel, sample, curSample);
            
            //outBlockLP.add(outBlockHP);
            //curSample = outBlockLP.getSample(channel, sample);
            //std::cout << "Current final sample: " << curSample << std::endl;
        }
    }
    
    outBufferLP.addFrom(0, 0, outBufferLP, 1, 0, outBufferLP.getNumSamples());
    outBufferHP.addFrom(0, 0, outBufferHP, 1, 0, outBufferHP.getNumSamples());
    
    buffer.copyFrom(0,0, outBufferLP, 0, 0, outBufferLP.getNumSamples());
    buffer.copyFrom(1,0, outBufferHP, 0, 0, outBufferHP.getNumSamples());
    buffer.applyGain(0.5f);
    
    /*
    float curInTrebleSample{0.f}, curOutTrebleSample{0.f};
    float prevInTrebleSample{0.f}, prevOutTrebleSample{0.f};
    
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
        auto next_bass_value = bassFreqModulator.getNextValue();
        
        curInSample = buffer.getSample (0, sample);
        std::cout << "Current bass in sample: " << curInSample <<std::endl;
        auto tmpCurSample = curInSample;
        for (int cascadeLength = 0; cascadeLength < 3; cascadeLength ++)
        {
            curOutSample = next_bass_value * tmpCurSample + prevInSample - next_bass_value * prevOutSample;
            tmpCurSample = curOutSample;
        }

        prevInSample = curInSample;
        prevOutSample = curOutSample;
        buffer.setSample(0, sample, curOutSample);
        std::cout << "Current bass out sample: " << curOutSample <<std::endl;
        
        auto next_treble_value = trebleFreqModulator.getNextValue();
        
        curInTrebleSample = buffer.getSample (1, sample);
        std::cout << "Current treble in sample: " << curInTrebleSample <<std::endl;

        tmpCurSample = curInTrebleSample;
        for (int cascadeLength = 0; cascadeLength < 4; cascadeLength ++)
        {
            curOutTrebleSample = next_treble_value * tmpCurSample + prevInTrebleSample - next_treble_value * prevOutTrebleSample;
            tmpCurSample = curOutTrebleSample;
        }

        prevInTrebleSample = curInTrebleSample;
        prevOutTrebleSample = curOutTrebleSample;
        buffer.setSample(1, sample, curOutTrebleSample);
        std::cout << "Current treble out sample: " << curOutTrebleSample <<std::endl;
    }*/
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
