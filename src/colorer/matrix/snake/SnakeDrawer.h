#pragma once

#include <memory>
#include "led/LedMatrix.h"
#include "colorer/Colorer.h"
#include "colors/ColorRGB.h"
#include "snake/Snake.h"

class SnakeDrawer : public Colorer<LedMatrix>
{
private:
    std::shared_ptr<const Snake> _snake;
    ColorRGB _headColor;
    ColorRGB _bodyColor;

public:
    SnakeDrawer(std::shared_ptr<const Snake> snake, ColorRGB headColor, ColorRGB bodyColor) : Colorer()
    {
        _snake = snake;
        _headColor = headColor;
        _bodyColor = bodyColor;
    }

    virtual void apply(std::shared_ptr<LedMatrix> matrix) const override
    {
        if(_snake->isDead())
            return;

        auto body = _snake->getBody();

        auto it = body.begin();

        matrix->getPixel(*it)->setColor(_headColor);

        it++;

        for(; it != body.end(); it++)
        {
            matrix->getPixel(*it)->setColor(_bodyColor);
        }
    }
};
