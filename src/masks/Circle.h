#pragma once

#include "LedMatrixMask.h"

class Circle : public LedMatrixMask
{
    protected:
        Vector2<uint16_t> _center;
        float _sqrRadius;
    public:
        Circle(LedMatrix* ledMatrix, Vector2<uint16_t> center, float radius) : LedMatrixMask(ledMatrix)
        {
            _ledMatrix = ledMatrix;
            _center = center;
            _sqrRadius = radius * radius;
        }

        virtual bool hasPixel(Vector2<uint16_t> position) const override
        {
            if(_sqrRadius <= 0)
                return false;
            return _center.sqrDistance(position) <= _sqrRadius;
        }
};