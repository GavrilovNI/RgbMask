#pragma once

#include <cmath>
#include "CycleAnimation.h"
#include "colors/ColorRGB.h"
#include "colors/ColorHSV.h"

class Snake : public CycleAnimation<LedMatrix>
{
private:
    ColorRGB _color;
public:
    Snake(float maxLength, ColorRGB color) : CycleAnimation(maxLength)
    {
        _color = color;
    }

    virtual void apply(LedMatrix* matrix) const
    {
        matrix->clear();
        int i;
        for(i = 0; i < matrix->getWidth() * matrix->getHeight() && i <= _currentTime - 1; i++)
        {
            uint8_t x = i / matrix->getHeight();
            uint8_t y = i % matrix->getHeight();
            if(x % 2 == 1)
                y = matrix->getHeight() - y - 1;
            matrix->getPixel(x, y)->setColor(_color);
        }
        if(i < matrix->getWidth() * matrix->getHeight() && i < _maxTime)
        {
            float lastPixelBrightness = _currentTime - i;
            uint8_t x = i / matrix->getHeight();
            uint8_t y = i % matrix->getHeight();
            if(x % 2 == 1)
                y = matrix->getHeight() - y - 1;

            ColorHSV color = _color.toHSV();
            color.setV(lastPixelBrightness);
            matrix->getPixel(x, y)->setColor(color);
        }
        
    }
};
