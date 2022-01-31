#pragma once
#include <memory>
#include <vector>
#include <cstdlib>
#include "Snake.h"
#include "SnakeMap.h"

class SnakeMapUpdater
{
private:
    
public:
    void onSnakeDied(std::shared_ptr<SnakeMap> snakeMap, std::shared_ptr<const Snake> snake)
    {
        auto snakeBody = snake->getBody();
        for(auto bodyPos : snakeBody)
        {
            snakeMap->addWall(bodyPos);
        }
        snakeMap->removeSnake(snake);
    }

    void onFoodEaten(std::shared_ptr<SnakeMap> snakeMap, Vector2<uint16_t> pos)
    {
        snakeMap->removeFood(pos);

        auto size = snakeMap->getSize();

        std::vector<Vector2<uint16_t>> emptyTilePoses;
        for(uint16_t y = 0; y < size.y; y++)
        {
            for(uint16_t x = 0; x < size.x; x++)
            {
                emptyTilePoses.push_back(Vector2<uint16_t>(x, y));
            }
        }

        int count = emptyTilePoses.size();
        if(count > 0)
        {
            int nextFoodPosId = std::rand() % count;
            snakeMap->addFood(emptyTilePoses[nextFoodPosId]);
        }
    }
};
