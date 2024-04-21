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

//[Headers] You can add your own extra header files here...
#include "BinaryData.h"
//[/Headers]

#include "PluginGui.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PluginGui::PluginGui ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    groupAILeslie.reset (new juce::GroupComponent (juce::String(),
                                                   TRANS ("AI Leslie")));
    addAndMakeVisible (groupAILeslie.get());
    groupAILeslie->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xffc81010));
    groupAILeslie->setColour (juce::GroupComponent::textColourId, juce::Colour (0xff431403));

    groupAILeslie->setBounds (150, 53, 208, 126);

    btnLeslie122.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (btnLeslie122.get());
    btnLeslie122->setButtonText (TRANS ("Leslie 122A"));
    btnLeslie122->addListener (this);
    btnLeslie122->setColour (juce::ToggleButton::textColourId, juce::Colour (0xff431403));

    btnLeslie122->setBounds (192, 79, 150, 24);

    btnLeslie147.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (btnLeslie147.get());
    btnLeslie147->setButtonText (TRANS ("Leslie 147"));
    btnLeslie147->addListener (this);
    btnLeslie147->setColour (juce::ToggleButton::textColourId, juce::Colour (0xff3b1000));

    btnLeslie147->setBounds (192, 123, 150, 24);

    groupSpectralDelay.reset (new juce::GroupComponent (juce::String(),
                                                        TRANS ("Spectral Delay Leslie")));
    addAndMakeVisible (groupSpectralDelay.get());
    groupSpectralDelay->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xffc81010));
    groupSpectralDelay->setColour (juce::GroupComponent::textColourId, juce::Colour (0xfff57b4f));

    groupSpectralDelay->setBounds (14, 203, 479, 302);

    sliderCutOff.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (sliderCutOff.get());
    sliderCutOff->setRange (500, 2000, 1);
    sliderCutOff->setSliderStyle (juce::Slider::LinearHorizontal);
    sliderCutOff->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCutOff->addListener (this);

    sliderCutOff->setBounds (65, 274, 67, 51);

    lblCutOff.reset (new juce::Label ("new label",
                                      TRANS ("Cut-off\n")));
    addAndMakeVisible (lblCutOff.get());
    lblCutOff->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblCutOff->setJustificationType (juce::Justification::centredLeft);
    lblCutOff->setEditable (false, false, false);
    lblCutOff->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblCutOff->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblCutOff->setBounds (64, 242, 86, 24);

    lblBalance.reset (new juce::Label ("new label",
                                       TRANS ("Bass/Treble balance\n"
                                       "\n")));
    addAndMakeVisible (lblBalance.get());
    lblBalance->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblBalance->setJustificationType (juce::Justification::centredLeft);
    lblBalance->setEditable (false, false, false);
    lblBalance->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblBalance->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblBalance->setBounds (33, 346, 142, 24);

    lblAmplitude.reset (new juce::Label ("new label",
                                         TRANS ("Amp modulation")));
    addAndMakeVisible (lblAmplitude.get());
    lblAmplitude->setFont (juce::Font (17.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblAmplitude->setJustificationType (juce::Justification::centredLeft);
    lblAmplitude->setEditable (false, false, false);
    lblAmplitude->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblAmplitude->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblAmplitude->setBounds (201, 332, 94, 48);

    lblStereo.reset (new juce::Label ("new label",
                                      TRANS ("Bass/Treble Stereo")));
    addAndMakeVisible (lblStereo.get());
    lblStereo->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblStereo->setJustificationType (juce::Justification::centredLeft);
    lblStereo->setEditable (false, false, false);
    lblStereo->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblStereo->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblStereo->setBounds (352, 234, 120, 40);

    btnR.reset (new juce::Label ("new label",
                                 TRANS ("R")));
    addAndMakeVisible (btnR.get());
    btnR->setFont (juce::Font (20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    btnR->setJustificationType (juce::Justification::centredLeft);
    btnR->setEditable (false, false, false);
    btnR->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    btnR->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    btnR->setBounds (446, 344, 22, 24);

    btnL.reset (new juce::Label ("new label",
                                 TRANS ("L\n")));
    addAndMakeVisible (btnL.get());
    btnL->setFont (juce::Font (20.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    btnL->setJustificationType (juce::Justification::centredLeft);
    btnL->setEditable (false, false, false);
    btnL->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    btnL->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    btnL->setBounds (358, 344, 22, 24);

    sliderLR.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (sliderLR.get());
    sliderLR->setRange (0, 1, 0.001);
    sliderLR->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    sliderLR->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderLR->addListener (this);

    sliderLR->setBounds (364, 370, 99, 96);

    groupCrossOver.reset (new juce::GroupComponent (juce::String(),
                                                    TRANS ("CrossOver")));
    addAndMakeVisible (groupCrossOver.get());
    groupCrossOver->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xffe68c6c));
    groupCrossOver->setColour (juce::GroupComponent::textColourId, juce::Colour (0xfff57b4f));

    groupCrossOver->setBounds (27, 226, 151, 262);

    groupModulation.reset (new juce::GroupComponent (juce::String(),
                                                     TRANS ("Modulation")));
    addAndMakeVisible (groupModulation.get());
    groupModulation->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xffe68c6c));
    groupModulation->setColour (juce::GroupComponent::textColourId, juce::Colour (0xfff57b4f));

    groupModulation->setBounds (185, 226, 144, 262);

    btnSlow.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (btnSlow.get());
    btnSlow->setButtonText (TRANS ("Slow"));
    btnSlow->addListener (this);

    btnSlow->setBounds (193, 282, 62, 24);

    btnFast.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (btnFast.get());
    btnFast->setButtonText (TRANS ("Fast"));
    btnFast->addListener (this);

    btnFast->setBounds (265, 282, 62, 24);

    groupPanPot.reset (new juce::GroupComponent (juce::String(),
                                                 TRANS ("Pan-Pot")));
    addAndMakeVisible (groupPanPot.get());
    groupPanPot->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xffe68c6c));
    groupPanPot->setColour (juce::GroupComponent::textColourId, juce::Colour (0xfff57b4f));

    groupPanPot->setBounds (336, 226, 144, 262);

    btnYes.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (btnYes.get());
    btnYes->setButtonText (TRANS ("Yes"));
    btnYes->addListener (this);

    btnYes->setBounds (357, 282, 62, 24);

    btnNo.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (btnNo.get());
    btnNo->setButtonText (TRANS ("No"));
    btnNo->addListener (this);

    btnNo->setBounds (425, 282, 62, 24);

    lblSpeed.reset (new juce::Label ("new label",
                                     TRANS ("Rotation speed\n")));
    addAndMakeVisible (lblSpeed.get());
    lblSpeed->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblSpeed->setJustificationType (juce::Justification::centredLeft);
    lblSpeed->setEditable (false, false, false);
    lblSpeed->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblSpeed->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblSpeed->setBounds (194, 234, 112, 40);

    sliderAmplitude.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (sliderAmplitude.get());
    sliderAmplitude->setRange (0, 0.9, 0.001);
    sliderAmplitude->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    sliderAmplitude->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderAmplitude->addListener (this);

    sliderAmplitude->setBounds (205, 370, 99, 96);

    sliderBalance.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (sliderBalance.get());
    sliderBalance->setRange (0, 1, 0.001);
    sliderBalance->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    sliderBalance->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderBalance->addListener (this);

    sliderBalance->setBounds (50, 370, 99, 96);


    //[UserPreSize]
    backImage = juce::ImageCache::getFromMemory(BinaryData::leslie4_jpg,
        BinaryData::leslie4_jpgSize);

    juce::ScaledImage(backImage, 2);

    btnLeslie122->setRadioGroupId (LeslieModels);
    btnLeslie147->setRadioGroupId (LeslieModels);
    btnLeslie122->setToggleState(true, juce::NotificationType::dontSendNotification);
    
    btnSlow->setRadioGroupId (RotationSpeed);
    btnFast->setRadioGroupId (RotationSpeed);
    btnSlow->setToggleState(true, juce::NotificationType::dontSendNotification);
    
    btnYes->setRadioGroupId (StereoOutput);
    btnNo->setRadioGroupId (StereoOutput);
    btnNo->setToggleState(true, juce::NotificationType::dontSendNotification);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    setSize (backImage.getWidth()/1.7, backImage.getHeight()/1.7);
    moveGroupsDown(190);
    std::cout<<"width: " << backImage.getWidth()<<"; height: " << backImage.getHeight();
    //[/Constructor]
}

PluginGui::~PluginGui()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupAILeslie = nullptr;
    btnLeslie122 = nullptr;
    btnLeslie147 = nullptr;
    groupSpectralDelay = nullptr;
    sliderCutOff = nullptr;
    lblCutOff = nullptr;
    lblBalance = nullptr;
    lblAmplitude = nullptr;
    lblStereo = nullptr;
    btnR = nullptr;
    btnL = nullptr;
    sliderLR = nullptr;
    groupCrossOver = nullptr;
    groupModulation = nullptr;
    btnSlow = nullptr;
    btnFast = nullptr;
    groupPanPot = nullptr;
    btnYes = nullptr;
    btnNo = nullptr;
    lblSpeed = nullptr;
    sliderAmplitude = nullptr;
    sliderBalance = nullptr;
    
    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PluginGui::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (juce::Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //g.drawImageAt (backImage, 0, 0);

    const auto width = backImage.getWidth() / 1.7f;
    const auto height = backImage.getHeight() / 1.7f;

    g.drawImage(backImage, {0, 0, width,  height} );
    //[/UserPaint]
}

void PluginGui::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PluginGui::buttonClicked (juce::Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == btnLeslie122.get())
    {
        //[UserButtonCode_btnLeslie122] -- add your button handler code here..
        //[/UserButtonCode_btnLeslie122]
    }
    else if (buttonThatWasClicked == btnLeslie147.get())
    {
        //[UserButtonCode_btnLeslie147] -- add your button handler code here..
        //[/UserButtonCode_btnLeslie147]
    }
    else if (buttonThatWasClicked == btnSlow.get())
    {
        //[UserButtonCode_btnSlow] -- add your button handler code here..
        //[/UserButtonCode_btnSlow]
    }
    else if (buttonThatWasClicked == btnFast.get())
    {
        //[UserButtonCode_btnFast] -- add your button handler code here..
        //[/UserButtonCode_btnFast]
    }
    else if (buttonThatWasClicked == btnYes.get())
    {
        //[UserButtonCode_btnYes] -- add your button handler code here..
        //[/UserButtonCode_btnYes]
    }
    else if (buttonThatWasClicked == btnNo.get())
    {
        //[UserButtonCode_btnNo] -- add your button handler code here..
        //[/UserButtonCode_btnNo]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PluginGui::sliderValueChanged (juce::Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == sliderCutOff.get())
    {
        //[UserSliderCode_sliderCutOff] -- add your slider handling code here..
        //[/UserSliderCode_sliderCutOff]
    }
    else if (sliderThatWasMoved == sliderLR.get())
    {
        //[UserSliderCode_sliderLR] -- add your slider handling code here..
        //[/UserSliderCode_sliderLR]
    }
    else if (sliderThatWasMoved == sliderAmplitude.get())
    {
        //[UserSliderCode_sliderAmplitude] -- add your slider handling code here..
        //[/UserSliderCode_sliderAmplitude]
    }
    else if (sliderThatWasMoved == sliderBalance.get())
    {
        //[UserSliderCode_sliderBalance] -- add your slider handling code here..
        //[/UserSliderCode_sliderBalance]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PluginGui::moveGroupsDown(int shift)
{
    auto moveLambda = [shift](juce::Component* component)
    {
        component->setTopLeftPosition(component->getX(), component->getY() + shift);
    };

    moveLambda(groupAILeslie.get());
    moveLambda(btnLeslie122.get());
    moveLambda(btnLeslie147.get());
    moveLambda(groupSpectralDelay.get());
    moveLambda(sliderCutOff.get());
    moveLambda(lblCutOff.get());
    moveLambda(lblBalance.get());
    moveLambda(lblAmplitude.get());
    moveLambda(lblStereo.get());
    moveLambda(btnR.get());
    moveLambda(btnL.get());
    moveLambda(sliderLR.get());
    moveLambda(groupCrossOver.get());
    moveLambda(groupModulation.get());
    moveLambda(btnSlow.get());
    moveLambda(btnFast.get());
    moveLambda(groupPanPot.get());
    moveLambda(btnYes.get());
    moveLambda(btnNo.get());
    moveLambda(lblSpeed.get());
    moveLambda(sliderAmplitude.get());
    moveLambda(sliderBalance.get());
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PluginGui" componentName=""
                 parentClasses="public juce::Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="" id="2a8806637c608952" memberName="groupAILeslie" virtualName=""
                  explicitFocusOrder="0" pos="150 53 208 126" outlinecol="ffc81010"
                  textcol="ff431403" title="AI Leslie"/>
  <TOGGLEBUTTON name="new toggle button" id="8ab70b18bcc38372" memberName="btnLeslie122"
                virtualName="" explicitFocusOrder="0" pos="192 79 150 24" txtcol="ff431403"
                buttonText="Leslie 122A" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="82500b4463aa60a8" memberName="btnLeslie147"
                virtualName="" explicitFocusOrder="0" pos="192 123 150 24" txtcol="ff3b1000"
                buttonText="Leslie 147" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <GROUPCOMPONENT name="" id="9c01b9be6de86113" memberName="groupSpectralDelay"
                  virtualName="" explicitFocusOrder="0" pos="14 203 479 302" outlinecol="ffc81010"
                  textcol="fff57b4f" title="Spectral Delay Leslie"/>
  <SLIDER name="new slider" id="b9a6f3df0255743e" memberName="sliderCutOff"
          virtualName="" explicitFocusOrder="0" pos="65 274 67 51" min="500.0"
          max="2000.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="b6f680a685ff6e8a" memberName="lblCutOff"
         virtualName="" explicitFocusOrder="0" pos="64 242 86 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Cut-off&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8f1d3a61c01f9c0d" memberName="lblBalance"
         virtualName="" explicitFocusOrder="0" pos="33 346 142 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Bass/Treble balance&#10;&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b44cea7f90b9d0a" memberName="lblAmplitude"
         virtualName="" explicitFocusOrder="0" pos="201 332 94 48" edTextCol="ff000000"
         edBkgCol="0" labelText="Amp modulation" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="17.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="28cc27f5fd45d043" memberName="lblStereo"
         virtualName="" explicitFocusOrder="0" pos="352 234 120 40" edTextCol="ff000000"
         edBkgCol="0" labelText="Bass/Treble Stereo" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c6c271a9ab282c1d" memberName="btnR" virtualName=""
         explicitFocusOrder="0" pos="446 344 22 24" edTextCol="ff000000"
         edBkgCol="0" labelText="R" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="20.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="93968889e2d45cdb" memberName="btnL" virtualName=""
         explicitFocusOrder="0" pos="358 344 22 24" edTextCol="ff000000"
         edBkgCol="0" labelText="L&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="20.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="4a5c225e37cc42d6" memberName="sliderLR"
          virtualName="" explicitFocusOrder="0" pos="364 370 99 96" min="0.0"
          max="1.0" int="0.001" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <GROUPCOMPONENT name="" id="4fbfcdfeb1768a78" memberName="groupCrossOver" virtualName=""
                  explicitFocusOrder="0" pos="27 226 151 262" outlinecol="ffe68c6c"
                  textcol="fff57b4f" title="CrossOver"/>
  <GROUPCOMPONENT name="" id="147275323f01ae0d" memberName="groupModulation" virtualName=""
                  explicitFocusOrder="0" pos="185 226 144 262" outlinecol="ffe68c6c"
                  textcol="fff57b4f" title="Modulation"/>
  <TOGGLEBUTTON name="new toggle button" id="99298539cc161620" memberName="btnSlow"
                virtualName="" explicitFocusOrder="0" pos="193 282 62 24" buttonText="Slow"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="d575001c780ce13c" memberName="btnFast"
                virtualName="" explicitFocusOrder="0" pos="265 282 62 24" buttonText="Fast"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <GROUPCOMPONENT name="" id="b12ad3fd1e93352d" memberName="groupPanPot" virtualName=""
                  explicitFocusOrder="0" pos="336 226 144 262" outlinecol="ffe68c6c"
                  textcol="fff57b4f" title="Pan-Pot"/>
  <TOGGLEBUTTON name="new toggle button" id="3241366c6224a686" memberName="btnYes"
                virtualName="" explicitFocusOrder="0" pos="357 282 62 24" buttonText="Yes"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="3db61d684d7fc270" memberName="btnNo"
                virtualName="" explicitFocusOrder="0" pos="425 282 62 24" buttonText="No"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="796b9d5120a2b76" memberName="lblSpeed" virtualName=""
         explicitFocusOrder="0" pos="194 234 112 40" edTextCol="ff000000"
         edBkgCol="0" labelText="Rotation speed&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="b333c53b21fc68d8" memberName="sliderAmplitude"
          virtualName="" explicitFocusOrder="0" pos="205 370 99 96" min="0.0"
          max="0.9" int="0.001" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="1530f04e789f3465" memberName="sliderBalance"
          virtualName="" explicitFocusOrder="0" pos="50 370 99 96" min="0.0"
          max="1.0" int="0.001" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

