#pragma once

#include <cmath>
#include "Animation.h"
#include "colors/ColorHSV.h"

class Rainbow45 : public Animation
{
private:
    uint32_t _height;
    float _pos;
public:
    Rainbow45(uint32_t length)
    {
        _height = length;
        _pos = 0;
    }

    virtual void MoveFrame(float delta)
    {
        _pos += delta;
        _pos = std::fmod(_pos, _height);
        if(_pos < 0)
            _pos += _height;
    }


    virtual void Apply(LedSnakeMatrix& matrix)
    {
        float step = 360.0f / _height;
        float h = _pos * step;

        for(int x = 0; x < matrix.getWidth() + matrix.getHeight(); x++)
        {
            ColorHSV color(h, 1.0f, 1.0f);
            for(int y = 0; y <= x && y < matrix.getHeight(); y++)
            {
                int realX = x - y;
                if(realX >= matrix.getWidth())
                    continue;
                matrix.getPixel(realX, y).setColor(color.toRGB());
            }

            h += step;
            h = std::fmod(h, 360.0f);
        }
    }
};
