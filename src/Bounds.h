#pragma once

#include <algorithm>
#include "Vector2.h"

template <typename T>
class Bounds
{
    private:
        Vector2<T> _first;
        Vector2<T> _second;

    public:

        Bounds()
        {
            
        }

        Bounds(Vector2<T> first, Vector2<T> second)
        {
            _first = first;
            _second = second;
        }

        bool isInside(Vector2<T> position)
        {
            return position.x >= getLeft() &&
                   position.x <= getRight() &&
                   position.y >= getDown() &&
                   position.y <= getUp();
        }

        T getLeft()
        {
            return std::min(_first.x, _second.x);
        }

        T getRight()
        {
            return std::max(_first.x, _second.x);
        }

        T getUp()
        {
            return std::max(_first.y, _second.y);
        }
        
        T getDown()
        {
            return std::min(_first.y, _second.y);
        }
};