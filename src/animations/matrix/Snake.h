#pragma once

#include <cmath>
#include "animations/CycleAnimation.h"
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

    virtual void apply(std::shared_ptr<LedMatrix> matrix) const
    {
        matrix->clear();
        int i;

        Vector2<uint16_t> matrixSize = matrix->getSize();

        for(i = 0; i < matrixSize.square() && i <= _currentTime - 1; i++)
        {
            uint8_t x = i / matrixSize.y;
            uint8_t y = i % matrixSize.y;
            if(x % 2 == 1)
                y = matrixSize.y - y - 1;
            matrix->getPixel(Vector2<uint16_t>(x, y))->setColor(_color);
        }
        if(i < matrixSize.square() && i < _maxTime)
        {
            float lastPixelBrightness = _currentTime - i;
            uint8_t x = i / matrixSize.y;
            uint8_t y = i % matrixSize.y;
            if(x % 2 == 1)
                y = matrixSize.y - y - 1;

            ColorHSV color = _color.toHSV();
            color.setV(lastPixelBrightness);
            matrix->getPixel(Vector2<uint16_t>(x, y))->setColor(color);
        }
        
    }
};
