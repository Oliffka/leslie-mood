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
    groupAILeslie->setColour (juce::GroupComponent::textColourId, juce::Colour (0xffed5117));

    groupAILeslie->setBounds (128, 224, 240, 142);

    btnLeslie122.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (btnLeslie122.get());
    btnLeslie122->setButtonText (TRANS ("Leslie 122"));
    btnLeslie122->addListener (this);
    btnLeslie122->setColour (juce::ToggleButton::textColourId, juce::Colour (0xff431403));

    btnLeslie122->setBounds (152, 252, 150, 24);

    btnLeslie147.reset (new juce::ToggleButton ("new toggle button"));
    addAndMakeVisible (btnLeslie147.get());
    btnLeslie147->setButtonText (TRANS ("Leslie 147"));
    btnLeslie147->addListener (this);
    btnLeslie147->setColour (juce::ToggleButton::textColourId, juce::Colour (0xff3b1000));

    btnLeslie147->setBounds (152, 292, 150, 24);

    groupDelayLine.reset (new juce::GroupComponent (juce::String(),
                                                    TRANS ("Delay Line Leslie")));
    addAndMakeVisible (groupDelayLine.get());
    groupDelayLine->setColour (juce::GroupComponent::outlineColourId, juce::Colour (0xffc81010));
    groupDelayLine->setColour (juce::GroupComponent::textColourId, juce::Colour (0xffed5117));

    groupDelayLine->setBounds (32, 384, 456, 246);

    sliderCutOff.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (sliderCutOff.get());
    sliderCutOff->setRange (20, 20000, 1);
    sliderCutOff->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    sliderCutOff->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    sliderCutOff->addListener (this);

    sliderCutOff->setBounds (72, 416, 67, 83);

    juce__slider2.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider2.get());
    juce__slider2->setRange (0, 10, 0);
    juce__slider2->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    juce__slider2->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    juce__slider2->addListener (this);

    juce__slider2->setBounds (64, 528, 83, 83);

    lblCutOff.reset (new juce::Label ("new label",
                                      TRANS ("Cut off\n")));
    addAndMakeVisible (lblCutOff.get());
    lblCutOff->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblCutOff->setJustificationType (juce::Justification::centredLeft);
    lblCutOff->setEditable (false, false, false);
    lblCutOff->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblCutOff->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblCutOff->setBounds (80, 400, 86, 24);

    lblBalance.reset (new juce::Label ("new label",
                                       TRANS ("Bass/Treble balance\n"
                                       "\n")));
    addAndMakeVisible (lblBalance.get());
    lblBalance->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblBalance->setJustificationType (juce::Justification::centredLeft);
    lblBalance->setEditable (false, false, false);
    lblBalance->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblBalance->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblBalance->setBounds (64, 512, 142, 24);

    lblBassDelay.reset (new juce::Label ("new label",
                                         TRANS ("Delay\n")));
    addAndMakeVisible (lblBassDelay.get());
    lblBassDelay->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblBassDelay->setJustificationType (juce::Justification::centredLeft);
    lblBassDelay->setEditable (false, false, false);
    lblBassDelay->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblBassDelay->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblBassDelay->setBounds (240, 520, 86, 24);

    lblBass.reset (new juce::Label ("new label",
                                    TRANS ("Bass\n")));
    addAndMakeVisible (lblBass.get());
    lblBass->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblBass->setJustificationType (juce::Justification::centredLeft);
    lblBass->setEditable (false, false, false);
    lblBass->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblBass->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblBass->setBounds (240, 389, 152, 32);

    lblBassLfo.reset (new juce::Label ("new label",
                                       TRANS ("LFO\n")));
    addAndMakeVisible (lblBassLfo.get());
    lblBassLfo->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblBassLfo->setJustificationType (juce::Justification::centredLeft);
    lblBassLfo->setEditable (false, false, false);
    lblBassLfo->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblBassLfo->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblBassLfo->setBounds (242, 414, 86, 24);

    juce__slider5.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider5.get());
    juce__slider5->setRange (0, 10, 0);
    juce__slider5->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    juce__slider5->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    juce__slider5->addListener (this);

    juce__slider5->setBounds (224, 432, 75, 80);

    juce__slider3.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider3.get());
    juce__slider3->setRange (0, 10, 0);
    juce__slider3->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    juce__slider3->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    juce__slider3->addListener (this);

    juce__slider3->setBounds (224, 536, 75, 80);

    lblHorn.reset (new juce::Label ("new label",
                                    TRANS ("Horn\n")));
    addAndMakeVisible (lblHorn.get());
    lblHorn->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblHorn->setJustificationType (juce::Justification::centredLeft);
    lblHorn->setEditable (false, false, false);
    lblHorn->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblHorn->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblHorn->setBounds (392, 387, 160, 40);

    lblBassDelay2.reset (new juce::Label ("new label",
                                          TRANS ("Delay\n")));
    addAndMakeVisible (lblBassDelay2.get());
    lblBassDelay2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblBassDelay2->setJustificationType (juce::Justification::centredLeft);
    lblBassDelay2->setEditable (false, false, false);
    lblBassDelay2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblBassDelay2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblBassDelay2->setBounds (384, 520, 86, 24);

    lblBassLfo2.reset (new juce::Label ("new label",
                                        TRANS ("LFO\n")));
    addAndMakeVisible (lblBassLfo2.get());
    lblBassLfo2->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    lblBassLfo2->setJustificationType (juce::Justification::centredLeft);
    lblBassLfo2->setEditable (false, false, false);
    lblBassLfo2->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    lblBassLfo2->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    lblBassLfo2->setBounds (392, 416, 86, 24);

    juce__slider6.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider6.get());
    juce__slider6->setRange (0, 10, 0);
    juce__slider6->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    juce__slider6->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    juce__slider6->addListener (this);

    juce__slider6->setBounds (368, 432, 83, 80);

    juce__slider7.reset (new juce::Slider ("new slider"));
    addAndMakeVisible (juce__slider7.get());
    juce__slider7->setRange (0, 10, 0);
    juce__slider7->setSliderStyle (juce::Slider::RotaryHorizontalVerticalDrag);
    juce__slider7->setTextBoxStyle (juce::Slider::TextBoxBelow, false, 80, 20);
    juce__slider7->addListener (this);

    juce__slider7->setBounds (376, 536, 67, 80);


    //[UserPreSize]
    backImage = juce::ImageCache::getFromMemory(BinaryData::leslie4_jpg,
        BinaryData::leslie4_jpgSize);

    juce::ScaledImage(backImage, 2);

    btnLeslie122->setRadioGroupId (LeslieModels);
    btnLeslie147->setRadioGroupId (LeslieModels);
    //[/UserPreSize]

    setSize (600, 400);

    //[Constructor] You can add your own custom stuff here..
    setSize (backImage.getWidth()/1.7, backImage.getHeight()/1.7);
    //setSize (800, 700);
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
    groupDelayLine = nullptr;
    sliderCutOff = nullptr;
    juce__slider2 = nullptr;
    lblCutOff = nullptr;
    lblBalance = nullptr;
    lblBassDelay = nullptr;
    lblBass = nullptr;
    lblBassLfo = nullptr;
    juce__slider5 = nullptr;
    juce__slider3 = nullptr;
    lblHorn = nullptr;
    lblBassDelay2 = nullptr;
    lblBassLfo2 = nullptr;
    juce__slider6 = nullptr;
    juce__slider7 = nullptr;


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
    else if (sliderThatWasMoved == juce__slider2.get())
    {
        //[UserSliderCode_juce__slider2] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider2]
    }
    else if (sliderThatWasMoved == juce__slider5.get())
    {
        //[UserSliderCode_juce__slider5] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider5]
    }
    else if (sliderThatWasMoved == juce__slider3.get())
    {
        //[UserSliderCode_juce__slider3] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider3]
    }
    else if (sliderThatWasMoved == juce__slider6.get())
    {
        //[UserSliderCode_juce__slider6] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider6]
    }
    else if (sliderThatWasMoved == juce__slider7.get())
    {
        //[UserSliderCode_juce__slider7] -- add your slider handling code here..
        //[/UserSliderCode_juce__slider7]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
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
                  explicitFocusOrder="0" pos="128 224 240 142" outlinecol="ffc81010"
                  textcol="ffed5117" title="AI Leslie"/>
  <TOGGLEBUTTON name="new toggle button" id="8ab70b18bcc38372" memberName="btnLeslie122"
                virtualName="" explicitFocusOrder="0" pos="152 252 150 24" txtcol="ff431403"
                buttonText="Leslie 122" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="new toggle button" id="82500b4463aa60a8" memberName="btnLeslie147"
                virtualName="" explicitFocusOrder="0" pos="152 292 150 24" txtcol="ff3b1000"
                buttonText="Leslie 147" connectedEdges="0" needsCallback="1"
                radioGroupId="0" state="0"/>
  <GROUPCOMPONENT name="" id="9c01b9be6de86113" memberName="groupDelayLine" virtualName=""
                  explicitFocusOrder="0" pos="32 384 456 246" outlinecol="ffc81010"
                  textcol="ffed5117" title="Delay Line Leslie"/>
  <SLIDER name="new slider" id="b9a6f3df0255743e" memberName="sliderCutOff"
          virtualName="" explicitFocusOrder="0" pos="72 416 67 83" min="20.0"
          max="20000.0" int="1.0" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxBelow" textBoxEditable="1" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <SLIDER name="new slider" id="c8bf6f97eb2605f0" memberName="juce__slider2"
          virtualName="" explicitFocusOrder="0" pos="64 528 83 83" min="0.0"
          max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="b6f680a685ff6e8a" memberName="lblCutOff"
         virtualName="" explicitFocusOrder="0" pos="80 400 86 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Cut off&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="8f1d3a61c01f9c0d" memberName="lblBalance"
         virtualName="" explicitFocusOrder="0" pos="64 512 142 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Bass/Treble balance&#10;&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="45a1f53740abae2" memberName="lblBassDelay"
         virtualName="" explicitFocusOrder="0" pos="240 520 86 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="d58eb09eabac2a84" memberName="lblBass" virtualName=""
         explicitFocusOrder="0" pos="240 389 152 32" edTextCol="ff000000"
         edBkgCol="0" labelText="Bass&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="b44cea7f90b9d0a" memberName="lblBassLfo"
         virtualName="" explicitFocusOrder="0" pos="242 414 86 24" edTextCol="ff000000"
         edBkgCol="0" labelText="LFO&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="f502a5581060d20e" memberName="juce__slider5"
          virtualName="" explicitFocusOrder="0" pos="224 432 75 80" min="0.0"
          max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="7d3aaa3df4993fb8" memberName="juce__slider3"
          virtualName="" explicitFocusOrder="0" pos="224 536 75 80" min="0.0"
          max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="new label" id="28cc27f5fd45d043" memberName="lblHorn" virtualName=""
         explicitFocusOrder="0" pos="392 387 160 40" edTextCol="ff000000"
         edBkgCol="0" labelText="Horn&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="c6c271a9ab282c1d" memberName="lblBassDelay2"
         virtualName="" explicitFocusOrder="0" pos="384 520 86 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Delay&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="new label" id="93968889e2d45cdb" memberName="lblBassLfo2"
         virtualName="" explicitFocusOrder="0" pos="392 416 86 24" edTextCol="ff000000"
         edBkgCol="0" labelText="LFO&#10;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="new slider" id="4a5c225e37cc42d6" memberName="juce__slider6"
          virtualName="" explicitFocusOrder="0" pos="368 432 83 80" min="0.0"
          max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="new slider" id="9b643261e87817f1" memberName="juce__slider7"
          virtualName="" explicitFocusOrder="0" pos="376 536 67 80" min="0.0"
          max="10.0" int="0.0" style="RotaryHorizontalVerticalDrag" textBoxPos="TextBoxBelow"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

