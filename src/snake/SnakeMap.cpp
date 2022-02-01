#include "SnakeMap.h"
#include "Snake.h"

SnakeMap::SnakeMap(Vector2<int32_t> size)
{
    _size = size;
}

Vector2<int32_t> SnakeMap::normalizePos(Vector2<int32_t> pos) const
{
    pos.x = (pos.x + _size.x) % _size.x;
    pos.y = (pos.y + _size.y) % _size.y;
    return pos;
}

void SnakeMap::addWall(Vector2<int32_t> pos)
{
    Vector2<int32_t> normalized = normalizePos(pos);
    _walls.emplace(normalized);
}

void SnakeMap::removeWall(Vector2<int32_t> pos)
{
    Vector2<int32_t> normalized = normalizePos(pos);
    _walls.erase(normalized);
}

void SnakeMap::addWall(Bounds<int32_t> wall)
{
    for(int y = wall.getDown(); y <= wall.getUp(); y++)
    {
        for(int x = wall.getLeft(); x <= wall.getRight(); x++)
        {
            Vector2<int32_t> normalized = normalizePos(Vector2<int32_t>(x, y));
            _walls.emplace(normalized);
        }
    }
}

void SnakeMap::removeWall(Bounds<int32_t> wall)
{
    for(int y = wall.getDown(); y <= wall.getUp(); y++)
    {
        for(int x = wall.getLeft(); x <= wall.getRight(); x++)
        {
            Vector2<int32_t> normalized = normalizePos(Vector2<int32_t>(x, y));
            _walls.erase(normalized);
        }
    }
}

void SnakeMap::addSnake(std::shared_ptr<const Snake> snake)
{
    _snakes.emplace(snake);
}

void SnakeMap::removeSnake(std::shared_ptr<const Snake> snake)
{
    _snakes.erase(snake);
}

void SnakeMap::addFood(Vector2<int32_t> pos)
{
    Vector2<int32_t> normalized = normalizePos(pos);
    _foods.emplace(normalized);
}

void SnakeMap::removeFood(Vector2<int32_t> pos)
{
    Vector2<int32_t> normalized = normalizePos(pos);
    _foods.erase(normalized);
}

bool SnakeMap::isWall(Vector2<int32_t> pos) const
{
    pos = normalizePos(pos);
    return _walls.count(pos) == 1;
}
bool SnakeMap::isSnake(Vector2<int32_t> pos) const
{
    pos = normalizePos(pos);
    for(auto snake : _snakes)
    {
        if(snake->isBody(pos))
            return true;
    }
    return false;
}

bool SnakeMap::isFood(Vector2<int32_t> pos) const
{
    pos = normalizePos(pos);
    return _foods.count(pos) == 1;
}

SnakeMapTile SnakeMap::getTile(Vector2<int32_t> pos) const
{
    if(isWall(pos))
        return SnakeMapTile::Wall;
    if(isSnake(pos))
        return SnakeMapTile::Snake;
    if(isFood(pos))
        return SnakeMapTile::Food;
    return SnakeMapTile::Empty;
}

Vector2<int32_t> SnakeMap::getSize() const
{
    return _size;
}
