#pragma once

#include <cstdint>
#include "LedMatrix.h"

class LedSnakeMatrix : public LedMatrix
{
    public:
        LedSnakeMatrix(uint16_t width, uint16_t height) : LedMatrix(width, height)
        {
        }

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t x, uint16_t y) override
        {
            uint16_t index = x * _height + (x % 2 == 0 ? y : _height - y - 1);
            return LedStrip::getPixel(index);
        }
};