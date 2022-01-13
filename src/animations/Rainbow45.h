#pragma once

#include <cmath>
#include "CycleAnimation.h"
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

        for(int x = 0; x < matrix->getWidth() + matrix->getHeight(); x++)
        {
            ColorHSV color(h, 1.0f, 1.0f);
            for(int y = 0; y <= x && y < matrix->getHeight(); y++)
            {
                int realX = x - y;
                if(realX >= matrix->getWidth())
                    continue;
                matrix->getPixel(realX, y)->setColor(color);
            }

            h += step;
            h = std::fmod(h, 360.0f);
        }
    }
};
