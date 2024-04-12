#include "GifComponent.h"

GifComponent::GifComponent() :
    jifObj(BinaryData::horn2_gif, BinaryData::horn2_gifSize)
{
    setOpaque(true);
    setBufferedToImage(true);
    int width  = jifObj.getWidth() > 0 ? jifObj.getWidth() : 600;
    int height  = jifObj.getHeight() > 0 ? jifObj.getHeight() : 400;
    setSize(width/1.32, height/1.32);
    startTimerHz(30);
}

void GifComponent::paint (juce::Graphics& g) { jifObj.paint(g, getLocalBounds().toFloat()); }
void GifComponent::timerCallback() { ++jifObj; repaint(); }
void GifComponent::resized() { jifObj.resetAnimation(); }
