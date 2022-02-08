#pragma once
#include <memory>
#include "colors/ColorRGB.h"
#include "GameLife.h"
#include "led/LedMatrix.h"
#include "colorer/Colorer.h"

class GameLifeColorer : public Colorer<LedMatrix>
{
private:
    std::shared_ptr<GameLife> _game;
    ColorRGB _lifeColor;
    ColorRGB _deathColor;
public:
    GameLifeColorer(std::shared_ptr<GameLife> game, ColorRGB lifeColor, ColorRGB deathColor = ColorRGB(0, 0, 0))
    {
        _game = game;
        _lifeColor = lifeColor;
        _deathColor = deathColor;
    }

    virtual void apply(std::shared_ptr<LedMatrix> matrix) const override
    {
        auto gameSize = _game->getSize();
        for(uint16_t y = 0; y < matrix->getSize().y && y < gameSize.y; y++)
        {
            for(uint16_t x = 0; x < matrix->getSize().x && x < gameSize.x; x++)
            {
                Vector2<uint16_t> pos(x, y);
                ColorRGB color = _game->hasLife(Vector2<int>(pos)) ? _lifeColor : _deathColor;
                matrix->getPixel(pos)->setColor(color);
            }
        }
    }
};
