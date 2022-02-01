#include "Snake.h"
#include "SnakeMap.h"
#include "SnakeMapUpdater.h"
#include <Arduino.h>

Vector2<uint16_t> directionToVector2(Direction direction)
{
    switch (direction)
    {
    case Direction::Up:
        return Vector2<uint16_t>(0, 1);
    case Direction::Right:
        return Vector2<uint16_t>(1, 0);
    case Direction::Down:
        return Vector2<uint16_t>(0, -1);
    case Direction::Left:
        return Vector2<uint16_t>(-1, 0);
    default:
        throw "not implemented";
    }
}

Direction turnRight(Direction direction)
{
    return (Direction)(((int)direction + 1) % ((int)Direction::Count));
}

Direction turnLeft(Direction direction)
{
    return (Direction)(((int)direction - 1 + (int)Direction::Count) % ((int)Direction::Count));
}

Snake::Snake(Vector2<uint16_t> pos, Direction direction, int initialLength)
{
    auto directionVector = -directionToVector2(direction);
    for(int i = 0; i < initialLength; i++)
    {
        _body.push_back(pos + directionVector * i);
    }
    _direction = direction;
    _died = false;
}

void Snake::move(std::shared_ptr<SnakeMap> snakeMap, std::shared_ptr<SnakeMapUpdater> snakeMapUpdater)
{
    if(_died)
        throw "Died";
    
    auto nextPos = _body.front() + directionToVector2(_direction);
    nextPos = snakeMap->normalizePos(nextPos);
    
    SnakeMapTile nextTile = snakeMap->getTile(nextPos);
    if(nextPos == _body.back())
    {
        nextTile = SnakeMapTile::Empty; // if snake want to eat tail, but tail is gonna move
    }

    switch (nextTile)
    {
    case SnakeMapTile::Wall:
    case SnakeMapTile::Snake:
        _died = true;
        snakeMapUpdater->onSnakeDied(snakeMap, shared_from_this());
        break;
    case SnakeMapTile::Empty:
        _body.pop_back();
        break;
    case SnakeMapTile::Food:
        snakeMapUpdater->onFoodEaten(snakeMap, nextPos);
        break;
    }

    if(_died == false)
    {
        _body.push_front(nextPos);
    }
}

void Snake::turnRight()
{
    _direction = ::turnRight(_direction);
}

void Snake::turnLeft()
{
    _direction = ::turnLeft(_direction);
}

bool Snake::isBody(Vector2<uint16_t> pos) const
{
    for(Vector2<uint16_t> bodyPos : _body)
    {
        if(bodyPos == pos)
            return true;
    }
    return false;
}

bool Snake::isDead() const
{
    return _died;
}

const std::list<Vector2<uint16_t>>& Snake::getBody() const
{
    return _body;
}

Direction Snake::getDirection() const
{
    return _direction;
}
