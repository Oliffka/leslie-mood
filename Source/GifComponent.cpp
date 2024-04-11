#include "GifComponent.h"

GifComponent::GifComponent() :
    jifObj(BinaryData::horn_gif, BinaryData::horn_gifSize)
{
    setOpaque(true);
    setBufferedToImage(true);
    int width  = jifObj.getWidth() > 0 ? jifObj.getWidth() : 600;
    int height  = jifObj.getHeight() > 0 ? jifObj.getHeight() : 400;
    setSize(width, height);
    startTimerHz(20);
}

void GifComponent::paint (juce::Graphics& g) { jifObj.paint(g, getLocalBounds().toFloat()); }
void GifComponent::timerCallback() { ++jifObj; repaint(); }
void GifComponent::resized() { jifObj.resetAnimation(); }
