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
class LeslieSpeakerPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    LeslieSpeakerPluginAudioProcessorEditor (LeslieSpeakerPluginAudioProcessor&);
    ~LeslieSpeakerPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LeslieSpeakerPluginAudioProcessor& audioProcessor;
    std::unique_ptr<PluginGui> pluginGui;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeslieSpeakerPluginAudioProcessorEditor)
};
