/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "PluginGui.h"

using namespace juce;
//==============================================================================
LeslieSpeakerPluginAudioProcessorEditor::LeslieSpeakerPluginAudioProcessorEditor (LeslieSpeakerPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    jifObj(BinaryData::horn_gif, BinaryData::horn_gifSize)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    pluginGui = std::make_unique<PluginGui>();
    addAndMakeVisible(pluginGui.get());

    setSize (pluginGui->getWidth(), pluginGui->getHeight());
    startTimerHz(10);
}

LeslieSpeakerPluginAudioProcessorEditor::~LeslieSpeakerPluginAudioProcessorEditor()
{
}

//==============================================================================
void LeslieSpeakerPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    
    jifObj.paint(g, getLocalBounds().toFloat());
}

void LeslieSpeakerPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void LeslieSpeakerPluginAudioProcessorEditor::timerCallback()
{
    ++jifObj;
    repaint();
}
