#pragma once

#include <cstdint>
#include "LedStrip.h"

class LedMatrix : public LedStrip
{
    protected:
        uint16_t _width, _height;

    public:
        LedMatrix(uint16_t width, uint16_t height) : LedStrip(width * height)
        {
            _width = width;
            _height = height;
        }

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t x, uint16_t y) = 0;

        uint16_t getWidth()
        {
            return _width;
        }

        uint16_t getHeight()
        {
            return _height;
        }
};
