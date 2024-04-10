/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include <memory>
#include "gif_loader/jifObject.hpp"

//==============================================================================
/**
*/
class PluginGui;
class LeslieSpeakerPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                 public juce::Timer
{
public:
    LeslieSpeakerPluginAudioProcessorEditor (LeslieSpeakerPluginAudioProcessor&);
    ~LeslieSpeakerPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LeslieSpeakerPluginAudioProcessor& audioProcessor;
    std::unique_ptr<PluginGui> pluginGui;
    jif::JifObject jifObj;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeslieSpeakerPluginAudioProcessorEditor)
};

