#pragma once

#include <cstdint>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include "AdafruitLedPixel.h"
#include "led/LedStrip.h"

class AdafruitLedStrip : public LedStrip, public Adafruit_NeoPixel
{
    public:
        AdafruitLedStrip(uint16_t pixelsCount, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800)
            : LedStrip(pixelsCount), Adafruit_NeoPixel(pixelsCount, pin, type)
        {
        }

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t index) const override
        {
            uint8_t *pixel;
            if (wOffset == rOffset)
            {
                pixel = &pixels[index * 3];
            }
            else
            {
                pixel = &pixels[index * 4];
            }

            return std::static_pointer_cast<LedPixel>(std::make_shared<AdafruitLedPixel>(pixel, rOffset, gOffset, bOffset, wOffset, brightness));
        }
};
