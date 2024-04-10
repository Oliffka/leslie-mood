//
//  jifFormat.h
//  LeslieSpeakerPlugin
//
//  Created by Olga Besedova on 11/04/2024.
//

#pragma once

#include <JuceHeader.h>
#include "jifLoader.hpp"
#include <memory>

namespace jif{

class Format
{
public:
    Format(){}
    bool valid(juce::InputStream& in) {
#if (JUCE_MAC || JUCE_IOS) && USE_COREGRAPHICS_RENDERING && JUCE_USE_COREIMAGE_LOADER
        return false;
#else
        loader = std::make_unique<Loader>(in);
        return loader->readHeader();
#endif
    }
    
    const Image& decodeImage() {
        loader->loadAnotherImage();
        return loader->getImage();
    };
    
    int getImageHeight() const
    {
        return loader->getImageHeight();
    }
    
    int getImageWidth() const
    {
        return loader->getImageWidth();
    }
    
private:
    std::unique_ptr<Loader> loader;
    
JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Format)
};
}
