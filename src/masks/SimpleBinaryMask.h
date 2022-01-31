#pragma once

#include <functional>
#include "Vector2.h"
#include "led/LedMatrix.h"
#include "BinaryLedMatrixMask.h"

class SimpleMask : public BinaryLedMatrixMask
{
    protected:
        std::function<bool(Vector2<uint16_t>)> _hasPixelFunc;
    public:
        SimpleMask(LedMatrix* ledMatrix, std::function<bool(Vector2<uint16_t>)> hasPixelFunc) : BinaryLedMatrixMask(ledMatrix)
        {
            _ledMatrix = ledMatrix;
            _hasPixelFunc = hasPixelFunc;
        }

        virtual bool hasPixel(Vector2<uint16_t> position) const override
        {
            return _hasPixelFunc(position);
        }
};