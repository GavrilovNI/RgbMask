#pragma once

#include "led/LedMatrix.h"
#include "colorer/Colorer.h"
#include "colors/ColorRGB.h"

class Solid : public Colorer<LedMatrix>
{
private:
    ColorRGB _color;

public:
    Solid(ColorRGB color) : Colorer()
    {
        _color = color;
    }

    virtual void apply(std::shared_ptr<LedMatrix> matrix) const override
    {
        for(uint16_t y = 0; y < matrix->getSize().y; y++)
        {
            for(uint16_t x = 0; x < matrix->getSize().x; x++)
            {
                matrix->getPixel(Vector2<uint16_t>(x, y))->setColor(_color);
            }
        }
    }
};
