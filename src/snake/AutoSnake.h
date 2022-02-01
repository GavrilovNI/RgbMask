#pragma once
#include <memory>
#include <vector>
#include <list>
#include <Arduino.h>
#include "SnakeMap.h"
#include "Snake.h"

class AutoSnake
{
private:
    std::shared_ptr<Snake> _snake;
    std::shared_ptr<SnakeMap> _snakeMap;

    std::list<SnakeMapTile> getAllTilesFromHeadInDirection(Direction direction)
    {
        std::list<SnakeMapTile> result;
        Bounds<uint16_t> mapBounds(Vector2<uint16_t>(0, 0), _snakeMap->getSize() - Vector2<uint16_t>(1, 1));
        Vector2<uint16_t> firstPos = _snake->getBody().front();
        Vector2<uint16_t> directionVector = directionToVector2(direction);

        Vector2<uint16_t> pos = firstPos;
        while(mapBounds.isInside(pos))
        {
            result.push_back(_snakeMap->getTile(pos));
            pos = pos + directionVector;
        }
        pos = _snakeMap->normalizePos(pos);
        while(pos != firstPos)
        {
            result.push_back(_snakeMap->getTile(pos));
            pos = pos + directionVector;
        }
        
        result.pop_front();
        return result;
    }

    bool hasTile(std::list<SnakeMapTile> tiles, SnakeMapTile tile)
    {
        for(auto currentTile : tiles)
        {
            if(currentTile == tile)
                return true;
        }
        return false;
    }

    int distanceToTile(std::list<SnakeMapTile> tiles, SnakeMapTile tile)
    {
        int i = 0;
        for(auto currentTile : tiles)
        {
            if(currentTile == tile)
                return i;
            i++;
        }
        return -1;
    }

public:
    AutoSnake(std::shared_ptr<Snake> snake, std::shared_ptr<SnakeMap> snakeMap)
    {
        _snake = snake;
        _snakeMap = snakeMap;
    }

    void decide()
    {
        auto frontTiles = getAllTilesFromHeadInDirection(_snake->getDirection());
        auto rightTiles = getAllTilesFromHeadInDirection(turnRight(_snake->getDirection()));
        auto leftTiles = getAllTilesFromHeadInDirection(turnLeft(_snake->getDirection()));

        bool needTurn = false;

        if(frontTiles.size() != 0 && (frontTiles.front() == SnakeMapTile::Snake || frontTiles.front() == SnakeMapTile::Wall))
        {
            needTurn = true;
            if(rightTiles.size() != 0 && (rightTiles.front() == SnakeMapTile::Snake || rightTiles.front() == SnakeMapTile::Wall))
            {
                _snake->turnLeft();
                return;
            }
            else if(leftTiles.size() != 0 && (leftTiles.front() == SnakeMapTile::Snake || leftTiles.front() == SnakeMapTile::Wall))
            {
                _snake->turnRight();
                return;
            }
        }

        if(needTurn == false && hasTile(frontTiles, SnakeMapTile::Food))
        {
            return;
        }

        int distanceToFoodInRight = distanceToTile(rightTiles, SnakeMapTile::Food);

        if(needTurn == false && distanceToFoodInRight == -1)
        {
            return;
        }

        
        int distanceToFoodInLeft = distanceToTile(leftTiles, SnakeMapTile::Food);

        if(distanceToFoodInRight < distanceToFoodInLeft)
        {
            _snake->turnRight();
        }
        else
        {
            _snake->turnLeft();
        }
    }
};
