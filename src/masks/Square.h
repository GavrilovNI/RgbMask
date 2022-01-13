#pragma once

#include "LedMatrixMask.h"
#include "Bounds.h"

class Square : public LedMatrixMask
{
    protected:
        Bounds<uint16_t> _bounds;
    public:
        Square(LedMatrix* ledMatrix, Bounds<uint16_t> bounds) : LedMatrixMask(ledMatrix)
        {
            _ledMatrix = ledMatrix;
            _bounds = bounds;
        }

        virtual bool hasPixel(Vector2<uint16_t> position) const override
        {
            return _bounds.isInside(position);
        }
};