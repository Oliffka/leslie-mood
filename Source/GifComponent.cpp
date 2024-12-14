#include "GifComponent.h"

/**
 * Initializes the GifComponent object with the provided GIF data, sets default properties,
 * configures the size, and starts the animation.
 */

GifComponent::GifComponent() :
    jifObj(BinaryData::horn2_gif, BinaryData::horn2_gifSize)
{
    setOpaque(true);
    
    // Enables buffering for smoother drawing.
    setBufferedToImage(true);
    
    // Set the component size.
    int width  = jifObj.getWidth() > 0 ? jifObj.getWidth() : 600;
    int height  = jifObj.getHeight() > 0 ? jifObj.getHeight() : 400;
    setSize(width/1.32, height/1.32);
    
    setRotationSpeed(true);
    startAnimation();
}

/**
 * Updates the rotation speed of the animation. If the timer is running, it adjusts the timer frequency.
 */
void GifComponent::setRotationSpeed(bool slowSpeed)
{
    currentSpeed = getRotationSpeed(slowSpeed);
    if (isTimerRunning())
    {
        startTimerHz(currentSpeed);
    }
}

int GifComponent::getRotationSpeed(bool isSlowMode) const
{
    return isSlowMode ? slowSpeedHz : fastSpeedHz;
}

void GifComponent::startAnimation()
{
    if (!isTimerRunning())
    {
        startTimerHz(currentSpeed);
    }
}

void GifComponent::stopAnimation()
{
    if (isTimerRunning())
    {
        stopTimer();
        jifObj.resetAnimation();
        repaint();
    }
}

/**
 * Handles custom drawing of the component.
 * Renders the current frame of the GIF within the component's bounds.
 */
void GifComponent::paint(juce::Graphics& g)
{
    jifObj.paint(g, getLocalBounds().toFloat());
}

/**
 * Called periodically by the timer to advance the animation to the next frame and repaint the component.
 */
void GifComponent::timerCallback()
{
    ++jifObj;
    repaint();
}

void GifComponent::resized() 
{
    jifObj.resetAnimation();
}
