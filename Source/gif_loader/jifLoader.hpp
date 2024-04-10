//
//  jifLoader.h
//  LeslieSpeakerPlugin
//
//  Created by Olga Besedova on 10/04/2024.
//

#pragma once
#include <JuceHeader.h>
#include "jifImage.hpp"

namespace jif {

class Loader
{
public:
    Loader(juce::InputStream& in);
    
    bool readHeader();
    
    void loadAnotherImage();
    
    int getImageWidth() const;
    
    int getImageHeight() const;
    
    const Image& getImage() const;
    
private:
    bool getSizeFromHeader();
    
    bool readPalette(const int numCols);
    
    int readDataBlock(juce::uint8* const dest);
    
    int readExtension();
    
    void clearTable();
    
    void initialise(const int inputCodeSize);
    
    int readLZWByte();
    
    int getCode(const int codeSize_, const bool shouldInitialise);
    
    bool readImage(const int interlace, const int transparent);
    
private:
    Image image;
    juce::InputStream& input;
    juce::uint8 buffer[260];
    juce::uint8 buf[16];
    juce::PixelARGB palette[256];
    bool dataBlockIsZero, fresh, finished;
    int imageWidth, imageHeight, transparent, numColours;
    int currentBit, lastBit, lastByteIndex;
    int codeSize, setCodeSize;
    int maxCode, maxCodeSize;
    int firstcode, oldcode;
    int clearCode, endCode;
    enum { maxGifCode = 1 << 12 };
    int table[2][maxGifCode];
    int stack[2 * maxGifCode];
    int* sp;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Loader)
};
}
