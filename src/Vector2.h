#pragma once
#include <Arduino.h>

template<typename T>
class Vector2
{
public:
    T x;
    T y;
    
    Vector2()
    {
        this->x = 0;
        this->y = 0;
    }

    Vector2(T x, T y)
    {
        this->x = x;
        this->y = y;
    }

    Vector2(const Vector2<T>& other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    Vector2<T> operator+(const Vector2<T>& other) const
    {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2<T> operator-(const Vector2<T>& other) const
    {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2<T> operator-() const
    {
        return Vector2(-x, -y);
    }

    Vector2<T> operator*(const float& value) const
    {
        return Vector2(x * value, y * value);
    }

    bool operator==(const Vector2<T>& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator<(const Vector2<T>& other) const
    {
        return x < other.x;
    }

    Vector2<T>& operator=(const Vector2<T>& other)
    {
        x = other.x;
        y = other.y;

        return *this;
    }

    float sqrDistance(Vector2<T> to) const
    {
        float xDist = 1.0f * x - to.x;
        float yDist = 1.0f * y - to.y;
        return xDist * xDist + yDist * yDist;
    }

    T square() const
    {
        return x * y;
    }

    String toString() const
    {
        return "Vector2(" + String(x) + "; " + String(y) + ")";
    }
};



