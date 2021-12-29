#pragma once

#include <cstdint>
#include <Adafruit_NeoPixel.h>
#include "LedPixel.h"

class LedStrip : public Adafruit_NeoPixel
{
    public:
        LedStrip(uint16_t pixelsCount, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800)
            : Adafruit_NeoPixel(pixelsCount, pin, type)
        {
        }

        virtual LedPixel GetPixel(uint16_t index) {

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

};
