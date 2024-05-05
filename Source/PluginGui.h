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
#include "./custom/SwitchButton.h"
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
    juce::Slider* getCutOffSlider()
    {
        return sliderCutOff.get();
    }

    juce::Slider* getBalanceSlider()
    {
        return sliderBalance.get();
    }

    juce::Slider* getAmplitudeSlider()
    {
        return sliderAmplitude.get();
    }

    juce::Slider* getBassFilterSlider()
    {
        return sliderBassFilter.get();
    }

    juce::Slider* getTrebleFilterSlider()
    {
        return sliderTrebleFilter.get();
    }

    juce::Button* getSpeedButton()
    {
        return speedSwitch.get();
    }
    
    juce::Button* getAnimationSwitchButton()
    {
        return animationSwitch.get();
    }

    void moveGroupsDown(int shift);
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
        LeslieModels = 1
    };
    
    std::unique_ptr<jux::SwitchButton> animationSwitch;
    std::unique_ptr<jux::SwitchButton> speedSwitch;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::GroupComponent> groupAILeslie;
    std::unique_ptr<juce::ToggleButton> btnLeslie122;
    std::unique_ptr<juce::ToggleButton> btnLeslie147;
    std::unique_ptr<juce::GroupComponent> groupSpectralDelay;
    std::unique_ptr<juce::Slider> sliderCutOff;
    std::unique_ptr<juce::Label> lblCutOff;
    std::unique_ptr<juce::Label> lblBalance;
    std::unique_ptr<juce::Label> lblAmplitude;
    std::unique_ptr<juce::Label> lblBassFilter;
    std::unique_ptr<juce::Slider> sliderTrebleFilter;
    std::unique_ptr<juce::GroupComponent> groupCrossOver;
    std::unique_ptr<juce::GroupComponent> groupModulation;
    std::unique_ptr<juce::Label> lblSpeed;
    std::unique_ptr<juce::Slider> sliderAmplitude;
    std::unique_ptr<juce::Slider> sliderBalance;
    std::unique_ptr<juce::Label> lblTrebleFilter;
    std::unique_ptr<juce::Slider> sliderBassFilter;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginGui)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

