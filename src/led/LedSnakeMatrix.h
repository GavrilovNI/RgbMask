#pragma once

#include <cstdint>
#include "LedMatrix.h"

class LedSnakeMatrix : public LedMatrix
{
    using LedStrip::getPixel;
    public:
        LedSnakeMatrix(Vector2<uint16_t> size) : LedMatrix(size)
        {
        }
        
        virtual std::shared_ptr<LedPixel> getPixel(Vector2<uint16_t> position) const override
        {
            uint16_t index = position.x * _size.y + (position.x % 2 == 0 ? position.y : _size.y - position.y - 1);
            return getPixel(index);
        }
};
