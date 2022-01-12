#pragma once

#include <cstdint>
#include <Adafruit_NeoPixel.h>
#include "AdafruitLedPixel.h"
#include "led/LedSnakeMatrix.h"

class AdafruitLedSnakeMatrix : public LedSnakeMatrix, public Adafruit_NeoPixel
{
    public:
        AdafruitLedSnakeMatrix(uint16_t width, uint16_t height, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800)
            : LedSnakeMatrix(width, height), Adafruit_NeoPixel(width * height, pin, type)
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

            return std::make_shared<AdafruitLedPixel>(pixel, rOffset, gOffset, bOffset, wOffset, brightness);
        }

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t x, uint16_t y) const override
        {
            return LedSnakeMatrix::getPixel(x, y);
        }
};
