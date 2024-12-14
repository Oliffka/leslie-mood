#pragma once
#include <JuceHeader.h>
#include "gif_loader/JifObject.h"

/**
 * GifComponent:
 * A component that handles the display and animation of a GIF.
 */

class GifComponent :
    public juce::Component,
    public juce::Timer
{
public:
    GifComponent();
    void paint (juce::Graphics&) override;
    
    // Overridden timer callback to update the animation frame on each timer tick.
    void timerCallback() override;
    void resized() override;
    
    // Sets the rotation speed of the GIF animation.
    void setRotationSpeed(bool slowSpeed);
    
    // Starts/stops the GIF animation by enabling/disabling the timer.
    void startAnimation();
    void stopAnimation();
    
private:
    int getRotationSpeed(bool isSlowMode) const;
    
    // Object for handling the GIF data and rendering frames.
    jif::JifObject jifObj;
    
    int currentSpeed{0};
    
    // Slow rotation speed for the animation, in Hertz.
    const int slowSpeedHz = 15;
    
    // Fast rotation speed for the animation, in Hertz.
    const int fastSpeedHz = 40;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GifComponent)
};
