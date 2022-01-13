#pragma once

#include <algorithm>
#include "Vector2.h"

template <typename T>
class Bounds
{
    private:
        T _minX, _maxX, _minY, _maxY;

    public:

        Bounds()
        {
            
        }

        Bounds(Vector2<T> first, Vector2<T> second)
        {
            _minX = std::min(first.x, second.x);
            _maxX = std::max(first.x, second.x);
            _minY = std::min(first.y, second.y);
            _maxY = std::max(first.y, second.y);
        }

        Bounds(T minX, T minY, T maxX, T maxY)
        {
            _minX = std::min(minX, maxX);
            _maxX = std::max(minX, maxX);
            _minY = std::min(minY, maxY);
            _maxY = std::max(minY, maxY);
        }

        bool isInside(Vector2<T> position) const
        {
            return position.x >= getLeft() &&
                   position.x <= getRight() &&
                   position.y >= getDown() &&
                   position.y <= getUp();
        }

        T getLeft() const
        {
            return _minX;
        }

        T getRight() const
        {
            return _maxX;
        }

        T getUp() const
        {
            return _maxY;
        }
        
        T getDown() const
        {
            return _minY;
        }
};