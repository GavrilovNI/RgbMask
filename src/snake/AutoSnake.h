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
        //Serial.println("getAllTiles");
        std::list<SnakeMapTile> result;
        Bounds<int32_t> mapBounds(Vector2<int32_t>(0, 0), _snakeMap->getSize() - Vector2<int32_t>(1, 1));
        Vector2<int32_t> firstPos = _snake->getBody().front();
        Vector2<int32_t> directionVector = directionToVector2(direction);

        //Serial.println((int)direction);
        //Serial.println(directionVector.toString());
        //Serial.println("getAllTiles2");
        Vector2<int32_t> pos = firstPos;
        while(mapBounds.isInside(pos))
        {
        //Serial.println("getAllTiles3");
        //Serial.println(pos.toString());
            result.push_back(_snakeMap->getTile(pos));
            pos = pos + directionVector;
        }
        pos = _snakeMap->normalizePos(pos);
        //Serial.println("getAllTiles3.5");
        //Serial.println(firstPos.toString());
        while(pos != firstPos)
        {
        //Serial.println("getAllTiles4");
        //Serial.println(pos.toString());
            result.push_back(_snakeMap->getTile(pos));
            pos = pos + directionVector;
        }
        
        //Serial.println("getAllTiles5");
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
        //Serial.println("decide0");
        auto frontTiles = getAllTilesFromHeadInDirection(_snake->getDirection());
        //Serial.println("decide1");
        auto rightTiles = getAllTilesFromHeadInDirection(turnRight(_snake->getDirection()));
        //Serial.println("decide2");
        auto leftTiles = getAllTilesFromHeadInDirection(turnLeft(_snake->getDirection()));
        //Serial.println("decide3");

        bool needTurn = false;

        //Serial.println("decide");
        //Serial.println(_snakeMap->getSize().toString());
        //Serial.println(_snake->getBody().front().toString());

        //Serial.println("frontTiles");
        //for(auto tile : frontTiles)
        //    Serial.print((int)tile);
        //Serial.println();

        //Serial.println("rightTiles");
        //for(auto tile : rightTiles)
        //    Serial.print((int)tile);
        //Serial.println();

        //Serial.println("leftTiles");
        //for(auto tile : leftTiles)
        //    Serial.print((int)tile);
        //Serial.println();
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
