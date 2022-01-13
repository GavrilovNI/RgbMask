#pragma once

#include <cmath>
#include "animations/CycleAnimation.h"
#include "colors/ColorHSV.h"

class Rainbow45 : public CycleAnimation<LedMatrix>
{
public:
    Rainbow45(uint32_t length) : CycleAnimation((float)length)
    {
    }

    virtual void apply(LedMatrix* matrix) const override
    {
        float step = 360.0f / _maxTime;
        float h = _currentTime * step;

        Vector2<uint16_t> matrixSize = matrix->getSize();

        for(int x = 0; x < matrixSize.x + matrixSize.y; x++)
        {
            ColorHSV color(h, 1.0f, 1.0f);
            for(int y = 0; y <= x && y < matrixSize.y; y++)
            {
                int realX = x - y;
                if(realX >= matrixSize.x)
                    continue;
                matrix->getPixel(Vector2<uint16_t>(realX, y))->setColor(color);
            }

            h += step;
            h = std::fmod(h, 360.0f);
        }
    }
};
