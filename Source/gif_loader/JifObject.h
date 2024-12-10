//
//  jifObject.h
//  LeslieSpeakerPlugin
//
//  Created by Olga Besedova on 11/04/2024.
//  Temporary implementation adapted from Mrugalla's GIFLoad repository.
//

#pragma once
#include "JifImage.h"

namespace jif {

class JifObject
{
public:
    JifObject();
    JifObject(const void* jifData, const size_t jifSize);
    
    void addImg(const Image& img);
    const size_t numImages() const noexcept;
    void init();
    void paint(juce::Graphics& g, const juce::Rectangle<float>& bounds);
    void operator++();
    void resetAnimation();
    
    int getWidth() const;
    int getHeight() const;
private:
    std::vector<Image> images;
    int readIdx{0};
    int imageWidth{0};
    int imageHeight{0};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(JifObject)
};
}
