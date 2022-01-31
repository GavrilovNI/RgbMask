#pragma once
#include <cstdint>
#include <vector>
#include <set>
#include <memory>
#include "Vector2.h"
#include "Bounds.h"

enum class SnakeMapTile
{
    Empty,
    Food,
    Wall,
    Snake
};

class Snake;

class SnakeMap
{
private:
    Vector2<uint16_t> _size;
    std::set<Vector2<uint16_t>> _walls;
    std::set<Vector2<uint16_t>> _foods;
    std::set<std::shared_ptr<const Snake>> _snakes;
    
public:
    SnakeMap(Vector2<uint16_t> size);

    Vector2<uint16_t> normalizePos(Vector2<uint16_t> pos) const;

    void addWall(Vector2<uint16_t> pos);

    void removeWall(Vector2<uint16_t> pos);

    void addWall(Bounds<uint16_t> wall);

    void removeWall(Bounds<uint16_t> wall);

    void addSnake(std::shared_ptr<const Snake> snake);

    void removeSnake(std::shared_ptr<const Snake> snake);

    void addFood(Vector2<uint16_t> pos);

    void removeFood(Vector2<uint16_t> pos);

    bool isWall(Vector2<uint16_t> pos) const;

    bool isSnake(Vector2<uint16_t> pos) const;

    bool isFood(Vector2<uint16_t> pos) const;

    SnakeMapTile getTile(Vector2<uint16_t> pos) const;

    Vector2<uint16_t> getSize() const;
};