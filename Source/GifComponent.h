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
    
private:
    jif::JifObject jifObj;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GifComponent)
};
