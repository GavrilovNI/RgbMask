#pragma once
#include <vector>
#include "Arduino.h"
#include "Vector2.h"

template<typename T>
class Matrix
{
private:
    Vector2<int> _size;
    std::vector<std::vector<T>> _data;
public:
    Matrix(Vector2<int> size)
    {
        _size = size;
        _data = std::vector<std::vector<T>>(size.y);
        for(int i = 0; i < size.y; i++)
        {
            _data[i] = std::vector<T>(size.x, T());
        }
    }

    Vector2<int> getSize()
    {
        return _size;
    }

    virtual T get(Vector2<int> pos) const
    {
        return _data[pos.y][pos.x];
    }

    virtual void set(Vector2<int> pos, const T& value)
    {
        _data[pos.y][pos.x] = value;
    }

    String toString()
    {
        String result = "";

        for(int y = 0; y < _size.y; y++)
        {
            for(int x = 0; x < _size.x; x++)
            {
                result += String(get(Vector2<int>(x, y))) + ", ";
            }
            result += "\n";
        }
        return result;
    }
};
