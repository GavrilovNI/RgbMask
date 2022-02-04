#pragma once

#include "tests/MillisTest.h"
#include "led/LedMatrix.h"

#include "snake/AutoSnake.h"
#include "snake/Snake.h"
#include "snake/SnakeMap.h"
#include "snake/SnakeMapUpdater.h"


#include "colorer/matrix/snake/SnakeMapDrawer.h"
#include "colorer/matrix/snake/SnakeDrawer.h"

class SnakeTest : public MillisTest
{
private:
    std::shared_ptr<SnakeMap> snakeMap;
    std::shared_ptr<SnakeMapUpdater> snakeMapUpdater = std::make_shared<SnakeMapUpdater>();\

    std::vector<std::shared_ptr<Snake>> snakes;
    std::vector<std::shared_ptr<AutoSnake>> autoSnakes;

    std::vector<std::shared_ptr<Colorer<LedMatrix>>> colorers;

    float snakeTime;
    int snakeStepTime = 200;

    bool moveSnake(std::shared_ptr<Snake> snake)
    {
        if(snake->isDead())
            return false;
        
        snake->move(snakeMap, snakeMapUpdater);
        return true;
    }

public:

    SnakeTest(std::shared_ptr<AdafruitLedStripContainer<AdafruitLedSnakeMatrix>> ledStrips, std::shared_ptr<LedMatrix> matrix) : MillisTest(ledStrips, matrix)
    {
        std::shared_ptr<Snake> snake1 = std::make_shared<Snake>(Vector2<int32_t>(3, 3), Direction::Right, 3);
        std::shared_ptr<Snake> snake2 = std::make_shared<Snake>(Vector2<int32_t>(7, 3), Direction::Left, 3);

        snakes.push_back(snake1);
        snakes.push_back(snake2);

        snakeMap = std::make_shared<SnakeMap>(Vector2<int32_t>(_matrix->getSize()));
        for(auto snake : snakes)
        {
            snakeMap->addSnake(snake);
            autoSnakes.push_back(std::make_shared<AutoSnake>(snake, snakeMap));
        }

        snakeMapUpdater->spawnFood(snakeMap);


        colorers.push_back(std::make_shared<SnakeMapDrawer>(snakeMap, ColorRGB(255, 0, 0), ColorRGB(255, 255, 0)));

        colorers.push_back(std::make_shared<SnakeDrawer>(snake1, ColorRGB(255, 0, 255), ColorRGB(0, 255, 0)));
        colorers.push_back(std::make_shared<SnakeDrawer>(snake2, ColorRGB(255, 0, 255), ColorRGB(0, 0, 255)));
    }

    virtual void loop(uint32_t delta) override
    {
        snakeTime += delta;

        _ledStrips->clear();

        int snakeMoves = (int)floor(snakeTime / snakeStepTime);
        snakeTime -= snakeMoves * snakeStepTime;

        for(int i = 0; i < snakeMoves; i++)
        {
            std::vector<std::shared_ptr<Snake>> snakesToMove = snakes;
            int deadSnakes = 0;

            for(auto autoSnake : autoSnakes)
            {
                autoSnake->decide();
                auto snake = autoSnake->getSnake();

                bool moved = moveSnake(snake);
                if(moved == false)
                    deadSnakes++;

                snakesToMove.erase(std::remove(snakesToMove.begin(), snakesToMove.end(), snake), snakesToMove.end());
            }

            for(auto snake : snakesToMove)
            {
                bool moved = moveSnake(snake);
                if(moved == false)
                    deadSnakes++;
            }
            
            if(deadSnakes == snakes.size())
            {
                delay(1000);
                ESP.restart();
            }
        }

        for(auto colorer : colorers)
            colorer->apply(_matrix);

        _ledStrips->show();
    }
};
