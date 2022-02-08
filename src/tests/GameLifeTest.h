#pragma once

#include "tests/MillisTest.h"
#include "led/LedMatrix.h"

#include "gameLife/GameLife.h"
#include "gameLife/GameLifeColorer.h"

#include "Arduino.h"

class GameLifeTest : public MillisTest
{
private:
    std::shared_ptr<GameLife> _gameLife;
    
    std::shared_ptr<Colorer<LedMatrix>> _colorer;

    float gameTime;
    const int gameStepTime = 200;
    int currentMove = 0;
    const int movesToReload = 50;

public:

    GameLifeTest(std::shared_ptr<AdafruitLedStripContainer<AdafruitLedSnakeMatrix>> ledStrips, std::shared_ptr<LedMatrix> matrix) : MillisTest(ledStrips, matrix)
    {
        _gameLife = std::make_shared<GameLife>(Vector2<int>(matrix->getSize()));
        _colorer = std::make_shared<GameLifeColorer>(_gameLife, ColorRGB(0, 255, 0));

        initializeRandom();
    }

    void initializeRandom()
    {
        auto gameSize = _gameLife->getSize();
        for(int y = 0; y < gameSize.y; y++)
        {
            for(int x = 0; x < gameSize.x; x++)
            {
                if(random(3) == 0)
                    _gameLife->setLife(Vector2<int>(x, y));
            }
        }
    }

    virtual void loop(uint32_t delta) override
    {
        gameTime += delta;

        _ledStrips->clear();

        int gameMoves = (int)floor(gameTime / gameStepTime);
        gameTime -= gameMoves * gameStepTime;

        for(int i = 0; i < gameMoves; i++)
        {
            //Serial.println(_gameLife->toString());
            _gameLife->apply(_gameLife->getNext());
            currentMove++;
            if(currentMove % movesToReload == 0)
            {
                initializeRandom();
            }
        }

        _colorer->apply(_matrix);

        _ledStrips->show();
    }
};
