#pragma once
#include <JuceHeader.h>
#include "gif_loader/jifObject.hpp"

class GifComponent :
    public juce::Component,
    public juce::Timer
{
public:
    GifComponent();
    void paint (juce::Graphics&) override;
    void timerCallback() override;
    void resized() override;
    
    void setRotationSpeed(bool slowSpeed);
    void startAnimation();
    void stopAnimation();
    
private:
    int getRotationSpeed(bool isSlowMode) const;
    jif::JifObject jifObj;
    int currentSpeed{0};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GifComponent)
};
