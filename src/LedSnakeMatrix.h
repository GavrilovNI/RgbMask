#pragma once

#include <cstdint>
#include "LedStrip.h"

class LedSnakeMatrix : public LedStrip
{
    private:
        uint16_t _width, _length;

    public:
        LedSnakeMatrix(uint16_t width, uint16_t length, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800)
            : LedStrip(width * length, pin, type)
        {
            _width = width;
            _length = length;
        }

        virtual LedPixel getPixel(uint16_t x, uint16_t y) {
            
            uint16_t index = y * _width + (y % 2 == 0 ? x : _width - x - 1);
            return LedStrip::getPixel(index);
        }

        uint16_t getWidth()
        {
            return _width;
        }

        uint16_t getLength()
        {
            return _length;
        }
};
