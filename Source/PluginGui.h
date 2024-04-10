/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.11

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PluginGui  : public juce::Component,
                   public juce::Button::Listener,
                   public juce::Slider::Listener
{
public:
    //==============================================================================
    PluginGui ();
    ~PluginGui() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    juce::Image backImage;

    enum RadioButtonIds
    {
        LeslieModels = 11
    };
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> groupAILeslie;
    std::unique_ptr<juce::ToggleButton> btnLeslie122;
    std::unique_ptr<juce::ToggleButton> btnLeslie147;
    std::unique_ptr<juce::GroupComponent> groupDelayLine;
    std::unique_ptr<juce::Slider> juce__slider;
    std::unique_ptr<juce::Slider> juce__slider2;
    std::unique_ptr<juce::Label> lblCutOff;
    std::unique_ptr<juce::Label> lblBalance;
    std::unique_ptr<juce::Label> lblBassDelay;
    std::unique_ptr<juce::Label> lblBass;
    std::unique_ptr<juce::Label> lblBassLfo;
    std::unique_ptr<juce::Slider> juce__slider5;
    std::unique_ptr<juce::Slider> juce__slider3;
    std::unique_ptr<juce::Label> lblHorn;
    std::unique_ptr<juce::Label> lblBassDelay2;
    std::unique_ptr<juce::Label> lblBassLfo2;
    std::unique_ptr<juce::Slider> juce__slider6;
    std::unique_ptr<juce::Slider> juce__slider7;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

