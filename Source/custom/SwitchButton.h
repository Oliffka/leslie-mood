/*
  ==============================================================================

    MIT License

    Copyright (c) 2020 Tal Aviram

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

namespace jux
{
//==============================================================================
/**

    Fancy looking toggable button. commonly used in modern UIs.

    @see juce::ToggableButton

*/
class SwitchButton : public juce::Button
{
public:
    SwitchButton (juce::String name, bool isInverted, bool isVertical = false)
        : Button ("SwitchButton"), isInverted (isInverted), isVertical (isVertical)
    {
        setClickingTogglesState (true);
        setToggleState(true, juce::NotificationType::sendNotification);
        addAndMakeVisible(switchCircle);
        switchCircle.setWantsKeyboardFocus (false);
        switchCircle.setInterceptsMouseClicks (false, false);
    }
    
    void setColors(juce::Colour switchCircleColour, juce::Colour switchBorder, juce::Colour switchOnBack, juce::Colour switchOffBack)
    {
        switchColour = switchCircleColour;
        switchOffBackgroundColour = switchOffBack;
        switchOnBackgroundColour = switchOnBack;
        switchBorderColour = switchBorder;
        
        switchCircle.setColour(switchColour);
    }

    void setMillisecondsToSpendMoving (int newValue)
    {
        millisecondsToSpendMoving = newValue;
    }
    
    void setOnText(const juce::String& text)
    {
        onText = text;
    }
    
    void setOffText(const juce::String& text)
    {
        offText = text;
    }


    void paintButton (juce::Graphics& g,
                      bool shouldDrawButtonAsHighlighted,
                      bool shouldDrawButtonAsDown) override
    {
        auto b = getSwitchBounds();
        auto cornerSize = (isVertical ? b.getWidth() : b.getHeight()) * 0.5;
        g.setColour (switchBorderColour);
        g.drawRoundedRectangle (b, cornerSize, 2.0f);
        g.setColour (getSwitchState() ? switchOnBackgroundColour : switchOffBackgroundColour);
        g.fillRoundedRectangle (b, cornerSize);
        
        juce::Path switchPath;
        switchPath.addRoundedRectangle (b, cornerSize, cornerSize);
        g.fillPath (switchPath);

        g.setColour(switchColour);
        g.drawText (getSwitchState() ? "  " + onText : offText + "  ", b, getSwitchState() ? juce::Justification::left : juce::Justification::right);
        
        juce::Rectangle<float> switchCircleBounds;
        if (! isVertical)
            switchCircleBounds = { getSwitchState() ? 1.5f + b.getRight() - b.getHeight() : b.getX() - 1.5f, b.getY(), b.getHeight(), b.getHeight() };
        else
            switchCircleBounds = {
                b.getX(),
                getSwitchState() ? b.getBottom() - b.getWidth() - 1.5f : b.getY() + 1.5f,
                b.getWidth(),
                b.getWidth()
            };
        animator.animateComponent (&switchCircle, switchCircleBounds.reduced (1).toNearestInt(), 1.0, millisecondsToSpendMoving, false, 0.5, 0.5);
    }

    void resized() override
    {
        Button::resized();
        auto b = getSwitchBounds();
        juce::Rectangle<float> switchCircleBounds;
        if (! isVertical)
            switchCircleBounds = { getSwitchState() ? b.getRight() - b.getHeight() : b.getX(), b.getY(), b.getHeight(), b.getHeight() };
        else
            switchCircleBounds = {
                b.getX(),
                getSwitchState() ? b.getBottom() - b.getWidth() : b.getY(),
                b.getHeight(),
                b.getHeight()
            };
        switchCircle.setBounds (switchCircleBounds.reduced (1).toNearestInt());
    }

private:
    int millisecondsToSpendMoving { 50 };

    bool getSwitchState() const
    {
        return isInverted ? ! getToggleState() : getToggleState();
    }
    bool isInverted = false;
    bool isVertical = false;

    juce::Rectangle<float> getSwitchBounds()
    {
        auto b = getLocalBounds().toFloat().reduced (4, 4);
        return b;
    }
    
    class SwitchCircle : public Component
    {
    public:
        SwitchCircle (juce::Colour colour): Component(), switchColour{colour}
        {}
        void paint (juce::Graphics& g) override
        {
            g.setColour(switchColour);
            g.fillEllipse (getLocalBounds().toFloat());
        }
        
        void setColour(juce::Colour colour)
        {
            switchColour = colour;
        }
    private:
        juce::Colour switchColour{juce::Colours::white};
        
    };
    
    juce::Colour switchColour{0xFFE68C6C};
    juce::Colour switchOnBackgroundColour = juce::Colours::transparentWhite;
    juce::Colour switchOffBackgroundColour = juce::Colours::transparentWhite;
    juce::Colour switchBorderColour = juce::Colour{0xFF431403}.withAlpha(0.5f);
    
    SwitchCircle switchCircle{switchColour};
    
    juce::ComponentAnimator animator;
    
    juce::String onText{};
    juce::String offText{};
};

} // namespace jux
