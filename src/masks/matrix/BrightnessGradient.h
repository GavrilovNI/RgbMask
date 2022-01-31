#pragma once

#include <algorithm>
#include "masks/LedMatrixMask.h"

class BrightnessGradient : public LedMatrixMask
{
    protected:
        uint8_t _length;
    public:
        BrightnessGradient(std::shared_ptr<LedMatrix> ledMatrix, uint8_t length) : LedMatrixMask(ledMatrix)
        {
            _length = length;
        }

        virtual uint8_t getPixelBrightness(Vector2<uint16_t> position) const override
        {
            uint8_t posX = position.x % _length;

            return (uint8_t)(255.0f - 255.0f * posX / _length);
        }
};