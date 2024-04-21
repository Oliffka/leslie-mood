/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <memory>

//==============================================================================
/**
*/
class PluginGui;
class GifComponent;

class LeslieSpeakerPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
{
public:
    LeslieSpeakerPluginAudioProcessorEditor (LeslieSpeakerPluginAudioProcessor&);
    ~LeslieSpeakerPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void updateGifSpeed(bool isSlow);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LeslieSpeakerPluginAudioProcessor& audioProcessor;
    
    std::unique_ptr<PluginGui> pluginGui;
    std::unique_ptr<GifComponent> gifComponent;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutOffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> balanceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> amplitudeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> panPotAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> speedAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> stereoAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeslieSpeakerPluginAudioProcessorEditor)
};

