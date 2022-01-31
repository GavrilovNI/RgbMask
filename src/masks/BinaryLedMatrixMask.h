#pragma once

#include <memory>
#include "LedMatrixMask.h"


class BinaryLedMatrixMask : public LedMatrixMask
{
    public:
        BinaryLedMatrixMask(std::shared_ptr<LedMatrix> ledMatrix) : LedMatrixMask(ledMatrix)
        {

        }

        uint8_t getPixelBrightness(Vector2<uint16_t> position) const override
        {
            return hasPixel(position) ? 255 : 0;
        }

        virtual bool hasPixel(Vector2<uint16_t> position) const = 0;

};
