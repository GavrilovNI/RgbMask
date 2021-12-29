#pragma once

#include <cstdint>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include "LedPixel.h"

class LedStrip : public Adafruit_NeoPixel
{
    public:
        LedStrip(uint16_t pixelsCount, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800)
            : Adafruit_NeoPixel(pixelsCount, pin, type)
        {
        }

        virtual LedPixel getPixel(uint16_t index) const {

            uint8_t *pixel;
            if (wOffset == rOffset)
            {
                pixel = &pixels[index * 3];
            }
            else
            {
                pixel = &pixels[index * 4];
            }

            return LedPixel(pixel, rOffset, gOffset, bOffset, wOffset, brightness);
        }

        std::vector<uint8_t> toBytes() const
        {
            std::vector<uint8_t> result;
            uint16_t pixelsCount = numPixels();
            for(int i = 0; i < pixelsCount; i++)
            {
                std::vector<uint8_t> pixelBytes = getPixel(i).toBytes();
                result.insert(result.end(), pixelBytes.begin(), pixelBytes.end());
            }
            return result;
        }

        void fromBytes(uint8_t* bytes)
        {
            uint16_t pixelsCount = numPixels();
            for(int i = 0; i < pixelsCount; i++)
            {
                getPixel(i).fromBytes(bytes + i * 3);
            }
        }

};
