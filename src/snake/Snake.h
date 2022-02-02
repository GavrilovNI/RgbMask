#pragma once
#include <list>
#include <memory>
#include "Vector2.h"

enum class Direction
{
    Up = 0,
    Right,
    Down,
    Left,
    Count
};

Vector2<int32_t> directionToVector2(Direction direction);
Direction turnRight(Direction direction);
Direction turnLeft(Direction direction);

class SnakeMap;
class SnakeMapUpdater;

class Snake : public std::enable_shared_from_this<Snake>
{
private:
    std::list<Vector2<int32_t>> _body;
    Direction _direction;
    bool _died;
    

public:
    int _snakeId;

    Snake(Vector2<int32_t> pos, Direction direction, int initialLength);

    void move(std::shared_ptr<SnakeMap> snakeMap, std::shared_ptr<SnakeMapUpdater> snakeMapUpdater);

    void turnRight();

    void turnLeft();

    bool isBody(Vector2<int32_t> pos) const;

    bool isDead() const;

    const std::list<Vector2<int32_t>>& getBody() const;

    Direction getDirection() const;
};

