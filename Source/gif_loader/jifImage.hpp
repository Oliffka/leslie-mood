//
//  jifImage.hpp
//  LeslieSpeakerPlugin
//
//  Created by Olga Besedova on 10/04/2024.
//

#pragma once
#include <JuceHeader.h>

namespace jif {

struct Image {
    Image() :
        image(),
        x(0),
        y(0),
        width(0),
        height(0)
    {}
    Image(const juce::Image&& img) :
        image(img),
        x(0),
        y(0),
        width(img.getWidth()),
        height(img.getHeight())
    {}
    void paint(juce::Graphics& g, const juce::Rectangle<float>& bounds) 
    {
        //const auto nY = y * bounds.getHeight();
        
        const auto realWidth = image.getWidth();
        const auto realHeight = image.getHeight();
        
        const auto nX = (bounds.getWidth() - realWidth) / 2;
        const auto nY = (bounds.getHeight() - realHeight) / 2;
        
        const auto nWidth = width * realWidth;
        const auto nHeight = height * realHeight;
        
        //const auto nWidth = width * bounds.getWidth();
        //const auto nHeight = height * bounds.getHeight();
        g.drawImage(image, { nX, nY, nWidth, nHeight });
    }
    
    bool isValid() const
    {
        return image.isValid();
    }
    
    //TODO: private members
    juce::Image image;
    float x, y, width, height;
};
}
