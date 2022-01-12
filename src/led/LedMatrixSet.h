#pragma once

#include <cstdint>
#include <vector>
#include "LedMatrix.h"



class LedMatrixSet : public LedMatrix, public Adafruit_NeoPixel
{
    public:
    enum Direction
    {
        Right,
        Down,
    };

    private:
        std::vector<LedMatrix*> _matrixes;
        Direction _direction;

    public:
        LedMatrixSet(std::vector<LedMatrix*> matrixes, Direction direction) : LedMatrix(0, 0)
        {
            _matrixes = matrixes;
            _direction = direction;

            uint16_t width = 0;
            uint16_t height = 0;

            for(int i = 0; i < _matrixes.size(); i++)
            {
                if(_direction == Direction::Right)
                {
                    if(_matrixes[0]->getHeight() != _matrixes[i]->getHeight())
                        throw "matrixes heights must be equal";
                    width += _matrixes[i]->getWidth();
                    height = _matrixes[i]->getHeight();
                }
                else if(_direction == Direction::Down)
                {
                    if(_matrixes[0]->getWidth() != _matrixes[i]->getWidth())
                        throw "matrixes widths must be equal";
                    width = _matrixes[i]->getWidth();
                    height += _matrixes[i]->getHeight();
                }
            }

            _width = width;
            _height = height;
        }

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t x, uint16_t y) const override
        {
            for(int i = 0; i < _matrixes.size(); i++)
            {
                LedMatrix* currMatrix = _matrixes[i];
                if(_direction == Direction::Right)
                {
                    uint16_t currMatrixWidth = currMatrix->getWidth();
                    if(x >= currMatrixWidth)
                    {
                        x -= currMatrixWidth;
                        continue;
                    }
                    else
                    {
                        return currMatrix->getPixel(x, y);
                    }
                }
                else if(_direction == Direction::Down)
                {
                    uint16_t currMatrixHeight = currMatrix->getHeight();
                    if(y >= currMatrixHeight)
                    {
                        y -= currMatrixHeight;
                        continue;
                    }
                    else
                    {
                        return currMatrix->getPixel(x, y);
                    }
                }
            }

            return nullptr;
        }

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t index) const override
        {
            return nullptr;
        }
};
