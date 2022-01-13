#pragma once

#include <cstdint>
#include <Adafruit_NeoPixel.h>
#include "AdafruitLedPixel.h"
#include "led/LedSnakeMatrix.h"

class AdafruitLedSnakeMatrix : public LedSnakeMatrix, public Adafruit_NeoPixel
{
    public:
        AdafruitLedSnakeMatrix(Vector2<uint16_t> size, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800)
            : LedSnakeMatrix(size), Adafruit_NeoPixel(size.square(), pin, type)
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

        virtual std::shared_ptr<LedPixel> getPixel(Vector2<uint16_t> position) const override
        {
            return LedSnakeMatrix::getPixel(position);
        }
};
