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

class LeslieSpeakerPluginAudioProcessorEditor  : 
    public juce::AudioProcessorEditor,
    public juce::Button::Listener
{
public:
    LeslieSpeakerPluginAudioProcessorEditor (LeslieSpeakerPluginAudioProcessor&);
    ~LeslieSpeakerPluginAudioProcessorEditor() override;

    //=============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void updateGifSpeed(bool isSlow);
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void buttonStateChanged (juce::Button* button) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LeslieSpeakerPluginAudioProcessor& audioProcessor;
    
    // Unique pointer to the pluginGui object, which contains most of the UI elements.
    std::unique_ptr<PluginGui> pluginGui;
    
    // Unique pointer to the gifComponent object, responsible for playing GIF animations.
    std::unique_ptr<GifComponent> gifComponent;
    
    // Attachments for user-configurable parameters, such as cutoff frequency,
    // bass/treble balance, and modulation-related settings.
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> cutOffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> balanceAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> amplitudeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> bassFilterOrderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> trebleFilterOrderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> speedAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LeslieSpeakerPluginAudioProcessorEditor)
};

