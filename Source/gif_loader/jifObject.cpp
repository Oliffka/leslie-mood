//
//  jifObject.cpp
//  LeslieSpeakerPlugin
//
//  Created by Olga Besedova on 11/04/2024.
//

#include "jifObject.hpp"
#include "jifFormat.h"

namespace jif {

JifObject::JifObject() : images()
{}

JifObject::JifObject(const void* jifData, const size_t jifSize) : images()
{
    juce::MemoryInputStream memoryInputStream(jifData, jifSize, true);
    Format format;
    if (format.valid(memoryInputStream))
    {
        while (!memoryInputStream.isExhausted())
        {
            const auto& img = format.decodeImage();
            if (img.isValid())
                addImg(img);
        }
        imageWidth = format.getImageWidth();
        imageHeight = format.getImageHeight();
    }
    init();
}

void JifObject::addImg(const Image& img)
{
    images.push_back(img);
}

const size_t JifObject::numImages() const noexcept
{
    return images.size();
}

void JifObject::init()
{
    auto maxWidth = 0.f;
    auto maxHeight = 0.f;
    for (auto& img : images) {
        const auto w = img.image.getWidth();
        const auto h = img.image.getHeight();
        maxWidth = maxWidth < w ? w : maxWidth;
        maxHeight = maxHeight < h ? h : maxHeight;
    }
    for (auto& img : images) {
        img.x /= maxWidth;
        img.y /= maxHeight;
        img.width /= maxWidth;
        img.height /= maxHeight;
    }
}

void JifObject::paint(juce::Graphics& g, const juce::Rectangle<float>& bounds)
{
    g.setImageResamplingQuality(juce::Graphics::highResamplingQuality);
    if (readIdx >= numImages())
    {
        readIdx = 0;
        g.fillAll(juce::Colours::white);
    }
    images[readIdx].paint(g, bounds);
}

void JifObject::operator++()
{
    ++readIdx;
}

void JifObject::resetAnimation()
{
    readIdx = 0;
}

int JifObject::getWidth() const
{
    return imageWidth;
}


int JifObject::getHeight() const
{
    return imageHeight;
}
}
