#pragma once

#include <array>
#include "Vector2.h"
#include "Matrix.h"

class GameLife
{
private:
    Vector2<int> _size;
    std::shared_ptr<Matrix<bool>> _game;
public:
    GameLife(Vector2<int> size)
    {
        _size = size;
        _game = std::make_shared<Matrix<bool>>(size);
    }

    void setLife(Vector2<int> pos)
    {
        _game->set(pos, true);
    }
    void setDeath(Vector2<int> pos)
    {
        _game->set(pos, false);
    }
    bool hasLife(Vector2<int> pos) const
    {
        return _game->get(pos);
    }

    virtual std::array<bool, 8> getNeighbours(Vector2<int> pos) const
    {
        std::array<bool, 8> result;

        int i = 0;
        for(int y = pos.y - 1; y <= pos.y + 1; y++)
        {
            for(int x = pos.x - 1; x <= pos.x + 1; x++)
            {
                if(x == pos.x && y == pos.y)
                    continue;
                if(x < 0 || x >= _size.x)
                    result[i] = false;
                else if(y < 0 || y >= _size.y)
                    result[i] = false;
                else
                    result[i] = hasLife(Vector2<int>(x, y));

                i++;
            }
        }
        return result;
    }

    Matrix<bool> getNext() const
    {
        Matrix<bool> newMatrix(_size);
        for(int y = 0; y < _size.y; y++)
        {
            for(int x = 0; x < _size.x; x++)
            {
                Vector2<int> pos = Vector2<int>(x, y);
                std::array<bool, 8> neighbours = getNeighbours(pos);
                int neighboursCount = 0;
                for(int i = 0; i < neighbours.size(); i++)
                {
                    if(neighbours[i])
                        neighboursCount++;
                }

                bool alive = hasLife(pos);
                if(alive)
                {
                    if(neighboursCount != 2 && neighboursCount != 3)
                        alive = false;
                }
                else
                {
                    if(neighboursCount == 3)
                        alive = true;
                }
                newMatrix.set(pos, alive);
            }
        }
        return newMatrix;
    }

    void apply(Matrix<bool> matrix)
    {
        auto matrixSize = matrix.getSize();
        if(matrixSize != _size)
            throw "Wrong matrix size.";

        for(int y = 0; y < matrixSize.y; y++)
        {
            for(int x = 0; x < matrixSize.x; x++)
            {
                Vector2<int> pos(x, y);
                bool value = matrix.get(pos);

                if(value)
                {
                    setLife(pos);
                }
                else
                {
                    setDeath(pos);
                }
            }
        }
    }

    Vector2<int> getSize()
    {
        return _size;
    }

    String toString()
    {
        return _game->toString();
    }
};
