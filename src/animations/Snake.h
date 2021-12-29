#pragma once

#include <cmath>
#include "Animation.h"
#include "colors/ColorRGB.h"
#include "colors/ColorHSV.h"

class Snake : public Animation
{
private:
    float _maxLength;
    float _currLength;
    ColorRGB _color;
public:
    Snake(float maxLength, ColorRGB color)
    {
        _maxLength = maxLength;
        _color = color;
        _currLength = 0;
    }

    virtual void MoveFrame(float delta)
    {
        _currLength += delta;
        _currLength = std::fmod(_currLength, _maxLength);
        if(_currLength < 0)
            _currLength += _maxLength;
    }


    virtual void Apply(LedSnakeMatrix& matrix)
    {
        matrix.clear();
        int i;
        for(i = 0; i < matrix.getWidth() * matrix.getHeight() && i <= _currLength - 1; i++)
        {
            uint8_t x = i / matrix.getHeight();
            uint8_t y = i % matrix.getHeight();
            if(x % 2 == 1)
                y = matrix.getHeight() - y - 1;
            matrix.getPixel(x, y).setColor(_color);
        }
        if(i < matrix.getWidth() * matrix.getHeight() && i < _maxLength)
        {
            float lastPixelBrightness = _currLength - i;
            uint8_t x = i / matrix.getHeight();
            uint8_t y = i % matrix.getHeight();
            if(x % 2 == 1)
                y = matrix.getHeight() - y - 1;

            ColorHSV color = _color.toHSV();
            color.setV(lastPixelBrightness);
            matrix.getPixel(x, y).setColor(color.toRGB());
        }
        
    }
};
