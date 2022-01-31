#pragma once

#include "masks/BinaryLedMatrixMask.h"
#include "Bounds.h"

class Square : public BinaryLedMatrixMask
{
    protected:
        Bounds<uint16_t> _bounds;
    public:
        Square(std::shared_ptr<LedMatrix> ledMatrix, Bounds<uint16_t> bounds) : BinaryLedMatrixMask(ledMatrix)
        {
            _bounds = bounds;
        }

        virtual bool hasPixel(Vector2<uint16_t> position) const override
        {
            return _bounds.isInside(position);
        }
};