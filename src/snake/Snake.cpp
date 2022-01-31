#include "Snake.h"
#include "SnakeMap.h"

Vector2<uint16_t> Snake::directionToVector2(Direction direction)
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

void Snake::move(std::shared_ptr<const SnakeMap> snakeMap)
{
    if(_died)
        throw "Died";
    
    auto nextPos = _body.front() + directionToVector2(_direction);
    nextPos = snakeMap->normalizePos(nextPos);
    
    _body.pop_back();
    _body.push_front(nextPos);
}

void Snake::turnRight()
{
    _direction = (Direction)(((int)_direction + 1) % ((int)Direction::Count));
}

void Snake::turnLeft()
{
    _direction = (Direction)(((int)_direction - 1 + (int)Direction::Count) % ((int)Direction::Count));
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
