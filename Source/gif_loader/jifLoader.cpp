//
//  jifLoader.cpp
//  LeslieSpeakerPlugin
//
//  Created by Olga Besedova on 10/04/2024.
//  Temporary implementation adapted from Mrugalla's GIFLoad repository.
//

#include "JifLoader.h"

namespace jif
{
    Loader::Loader(juce::InputStream& in)
            : input(in),
            dataBlockIsZero(false), fresh(false), finished(false),
            imageWidth(0), imageHeight(0), transparent(-1), numColours(0),
            currentBit(0), lastBit(0), lastByteIndex(0),
            codeSize(0), setCodeSize(0), maxCode(0), maxCodeSize(0),
            firstcode(0), oldcode(0), clearCode(0), endCode(0)
        {}

    bool Loader::readHeader()
    {
        if (!getSizeFromHeader())
            return false;

        if (input.read(buf, 3) != 3)
            return false;

        numColours = 2 << (buf[0] & 7);

        if ((buf[0] & 0x80) == 0)
            return false;

        readPalette(numColours);
        return true;
    }

    int Loader::getImageWidth() const
    {
        return imageWidth;
    }
    
    int Loader::getImageHeight() const
    {
        return imageHeight;
    }
    
    const Image& Loader::getImage() const
    {
        return image;
    }

    void Loader::loadAnotherImage()
    {
        for (;;) 
        {
            if (input.read(buf, 1) != 1 || buf[0] == ';') break;

            if (buf[0] == '!') 
            {
                if (readExtension())
                    continue;
                break;
            }

            if (buf[0] != ',') continue;

            if (input.read(buf, 9) == 9) 
            {
                const auto imageX = (int)juce::ByteOrder::littleEndianShort(buf + 0);
                const auto imageY = (int)juce::ByteOrder::littleEndianShort(buf + 2);
                imageWidth = (int)juce::ByteOrder::littleEndianShort(buf + 4);
                imageHeight = (int)juce::ByteOrder::littleEndianShort(buf + 6);

                numColours = 2 << (buf[8] & 7);

                if ((buf[8] & 0x80) != 0)
                    if (!readPalette(numColours))
                        break;

                const auto pxlFormat = transparent >= 0 ? juce::Image::ARGB : juce::Image::RGB;
                image = juce::Image(pxlFormat, imageWidth, imageHeight, transparent >= 0);
                image.x = imageX;
                image.y = imageY;

                image.image.getProperties()->set("originalImageHadAlpha", transparent >= 0);

                readImage((buf[8] & 0x40) != 0, transparent);
            }
            break;
        }
    }

    bool Loader::getSizeFromHeader()
    {
        char b[6];

        if (input.read(b, 6) == 6
            && (strncmp("GIF87a", b, 6) == 0
                || strncmp("GIF89a", b, 6) == 0)) {
            if (input.read(b, 4) == 4) {
                imageWidth = (int)juce::ByteOrder::littleEndianShort(b);
                imageHeight = (int)juce::ByteOrder::littleEndianShort(b + 2);
                return imageWidth > 0 && imageHeight > 0;
            }
        }

        return false;
    }

    bool Loader::readPalette(const int numCols)
    {
        for (int i = 0; i < numCols; ++i) {
            juce::uint8 rgb[4];
            input.read(rgb, 3);
            palette[i].setARGB(0xff, rgb[0], rgb[1], rgb[2]);
            palette[i].premultiply();
        }
        return true;
    }

    int Loader::readDataBlock(juce::uint8* const dest)
    {
        juce::uint8 n;
        if (input.read(&n, 1) == 1) {
            dataBlockIsZero = (n == 0);

            if (dataBlockIsZero || (input.read(dest, n) == n))
                return n;
        }

        return -1;
    }

    int Loader::readExtension()
    {
        juce::uint8 type;
        if (input.read(&type, 1) != 1)
            return false;

        juce::uint8 b[260];
        int n = 0;

        if (type == 0xf9) 
        {
            n = readDataBlock(b);
            if (n < 0)
                return 1;

            if ((b[0] & 1) != 0)
                transparent = b[3];
        }

        do {
            n = readDataBlock(b);
        } while (n > 0);

        return n >= 0;
    }

    void Loader::clearTable()
    {
        int i;
        for (i = 0; i < clearCode; ++i) {
            table[0][i] = 0;
            table[1][i] = i;
        }

        for (; i < maxGifCode; ++i) {
            table[0][i] = 0;
            table[1][i] = 0;
        }
    }

    void Loader::initialise(const int inputCodeSize)
    {
        setCodeSize = inputCodeSize;
        codeSize = setCodeSize + 1;
        clearCode = 1 << setCodeSize;
        endCode = clearCode + 1;
        maxCodeSize = 2 * clearCode;
        maxCode = clearCode + 2;

        getCode(0, true);

        fresh = true;
        clearTable();
        sp = stack;
    }

    int Loader::readLZWByte()
    {
        if (fresh)
        {
            fresh = false;

            for (;;)
            {
                firstcode = oldcode = getCode(codeSize, false);

                if (firstcode != clearCode)
                    return firstcode;
            }
        }

        if (sp > stack)
            return *--sp;

        int code;

        while ((code = getCode(codeSize, false)) >= 0)
        {
            if (code == clearCode)
            {
                clearTable();
                codeSize = setCodeSize + 1;
                maxCodeSize = 2 * clearCode;
                maxCode = clearCode + 2;
                sp = stack;
                firstcode = oldcode = getCode(codeSize, false);
                return firstcode;
            }
            else if (code == endCode)
            {
                if (dataBlockIsZero)
                    return -2;

                juce::uint8 buf[260];
                int n;

                while ((n = readDataBlock(buf)) > 0)
                {
                }

                if (n != 0)
                    return -2;
            }

            const int incode = code;

            if (code >= maxCode)
            {
                *sp++ = firstcode;
                code = oldcode;
            }

            while (code >= clearCode)
            {
                *sp++ = table[1][code];
                if (code == table[0][code])
                    return -2;

                code = table[0][code];
            }

            *sp++ = firstcode = table[1][code];

            if ((code = maxCode) < maxGifCode)
            {
                table[0][code] = oldcode;
                table[1][code] = firstcode;
                ++maxCode;

                if (maxCode >= maxCodeSize && maxCodeSize < maxGifCode)
                {
                    maxCodeSize <<= 1;
                    ++codeSize;
                }
            }

            oldcode = incode;

            if (sp > stack)
                return *--sp;
        }

        return code;
    }

    int Loader::getCode(const int codeSize_, const bool shouldInitialise)
    {
        if (shouldInitialise)
        {
            currentBit = 0;
            lastBit = 0;
            finished = false;
            return 0;
        }

        if ((currentBit + codeSize_) >= lastBit)
        {
            if (finished)
                return -1;

            buffer[0] = buffer[lastByteIndex - 2];
            buffer[1] = buffer[lastByteIndex - 1];

            const int n = readDataBlock(buffer + 2);

            if (n == 0)
                finished = true;

            lastByteIndex = 2 + n;
            currentBit = (currentBit - lastBit) + 16;
            lastBit = (2 + n) * 8;
        }

        int result = 0;
        int i = currentBit;

        for (int j = 0; j < codeSize_; ++j)
        {
            result |= ((buffer[i >> 3] & (1 << (i & 7))) != 0) << j;
            ++i;
        }

        currentBit += codeSize_;
        return result;
    }

    bool Loader::readImage(const int interlace, const int transparent)
    {
        juce::uint8 c;
        if (input.read(&c, 1) != 1)
            return false;

        initialise(c);

        if (transparent >= 0)
            palette[transparent].setARGB(0, 0, 0, 0);

        int xpos = 0, ypos = 0, yStep = 8, pass = 0;

        const juce::Image::BitmapData destData(image.image, juce::Image::BitmapData::writeOnly);
        juce::uint8* p = destData.getPixelPointer(0, 0);
        const bool hasAlpha = image.image.hasAlphaChannel();

        for (;;) {
            const int index = readLZWByte();
            if (index < 0)
                break;

            if (hasAlpha)
                ((juce::PixelARGB*)p)->set(palette[index]);
            else
                ((juce::PixelRGB*)p)->set(palette[index]);

            p += destData.pixelStride;

            if (++xpos == destData.width) {
                xpos = 0;

                if (interlace) {
                    ypos += yStep;

                    while (ypos >= destData.height) {
                        switch (++pass)
                        {
                        case 1:     ypos = 4; yStep = 8; break;
                        case 2:     ypos = 2; yStep = 4; break;
                        case 3:     ypos = 1; yStep = 2; break;
                        default:    return true;
                        }
                    }
                }
                else {
                    if (++ypos >= destData.height)
                        break;
                }

                p = destData.getPixelPointer(xpos, ypos);
            }
        }

        return true;
    }
};
