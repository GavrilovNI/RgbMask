#pragma once

#include <cstdint>
#include "LedStrip.h"

class LedSnakeMatrix : public LedStrip
{
    private:
        uint16_t _width, _height;

    public:
        LedSnakeMatrix(uint16_t width, uint16_t height, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800)
            : LedStrip(width * height, pin, type)
        {
            _width = width;
            _height = height;
        }

        virtual LedPixel getPixel(uint16_t x, uint16_t y) {
            
            uint16_t index = x * _height + (x % 2 == 0 ? y : _height - y - 1);
            return LedStrip::getPixel(index);
        }

        uint16_t getWidth()
        {
            return _width;
        }

        uint16_t getHeight()
        {
            return _height;
        }
};
