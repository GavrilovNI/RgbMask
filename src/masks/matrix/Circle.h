#pragma once

#include <algorithm>
#include "masks/LedMatrixMask.h"

class Circle : public LedMatrixMask
{
    protected:
        Vector2<uint16_t> _center;
        float _sqrRadiusMin;
        float _sqrRadiusMax;
    public:
        Circle(std::shared_ptr<LedMatrix> ledMatrix, Vector2<uint16_t> center, float radius1, float radius2) : LedMatrixMask(ledMatrix)
        {
            _center = center;
            float sqrRadius1 = radius1 * radius1;
            float sqrRadius2 = radius2 * radius2;
            _sqrRadiusMin = std::min(sqrRadius1, sqrRadius2);
            _sqrRadiusMax = std::max(sqrRadius1, sqrRadius2);
        }
        Circle(std::shared_ptr<LedMatrix> ledMatrix, Vector2<uint16_t> center, float radius1) : Circle(ledMatrix, center, radius1, radius1)
        {
        }

        virtual uint8_t getPixelBrightness(Vector2<uint16_t> position) const override
        {
            float sqrDistance = _center.sqrDistance(position);

            if(sqrDistance <= _sqrRadiusMin)
                return 255;
            
            if(sqrDistance <= _sqrRadiusMax)
            {
                return (uint8_t)(255.0 - 255.0 * (sqrDistance - _sqrRadiusMin) / (_sqrRadiusMax - _sqrRadiusMin));
            }

            return 0;
        }
};