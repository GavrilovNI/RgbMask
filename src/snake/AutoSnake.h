#pragma once
#include <memory>
#include <vector>
#include <list>
#include <utility>
#include <tuple>
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
        Bounds<int32_t> mapBounds(Vector2<int32_t>(0, 0), _snakeMap->getSize() - Vector2<int32_t>(1, 1));
        Vector2<int32_t> firstPos = _snake->getBody().front();
        Vector2<int32_t> directionVector = directionToVector2(direction);

        Vector2<int32_t> pos = firstPos;
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

        bool canGoForward = frontTiles.size() != 0 && frontTiles.front() != SnakeMapTile::Snake && frontTiles.front() != SnakeMapTile::Wall;
        bool canGoRight = rightTiles.size() != 0 && rightTiles.front() != SnakeMapTile::Snake && rightTiles.front() != SnakeMapTile::Wall;
        bool canGoLeft = leftTiles.size() != 0 && leftTiles.front() != SnakeMapTile::Snake && leftTiles.front() != SnakeMapTile::Wall;

        int distanceToFoodInFront = distanceToTile(frontTiles, SnakeMapTile::Food);
        int distanceToFoodInRight = distanceToTile(rightTiles, SnakeMapTile::Food);
        int distanceToFoodInLeft = distanceToTile(leftTiles, SnakeMapTile::Food);

        typedef std::tuple<Direction, bool, int> Choise;
        std::vector<Choise> choises;
        choises.push_back(std::make_tuple(Direction::Up, canGoForward, distanceToFoodInFront));
        choises.push_back(std::make_tuple(Direction::Right, canGoRight, distanceToFoodInRight));
        choises.push_back(std::make_tuple(Direction::Left, canGoLeft, distanceToFoodInLeft));

        std::sort(choises.begin(), choises.end(), [](Choise a, Choise b){
            if(std::get<2>(a) == -1)
            {
                if(std::get<0>(a) == Direction::Up && std::get<2>(b) == -1)
                    return true;
                return false;
            }
                
            if(std::get<2>(b) == -1)
                return true;

            return std::get<2>(a) < std::get<2>(b);
        });

        for(auto choise : choises)
        {
            if(std::get<1>(choise))
            {
                switch (std::get<0>(choise))
                {
                case Direction::Right:
                    _snake->turnRight();
                    break;
                case Direction::Left:
                    _snake->turnLeft();
                    break;
                default:
                    break;
                }
                break;
            }
        }

    }
};
