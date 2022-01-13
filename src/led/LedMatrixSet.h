#pragma once

#include <cstdint>
#include <vector>
#include "LedMatrix.h"



class LedMatrixSet : public LedMatrix
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
        LedMatrixSet(std::vector<LedMatrix*> matrixes, Direction direction) : LedMatrix(Vector2<uint16_t>(0, 0))
        {
            _matrixes = matrixes;
            _direction = direction;

            Vector2<uint16_t> size(0, 0);

            for(int i = 0; i < _matrixes.size(); i++)
            {
                Vector2<uint16_t> currMatrixSize = _matrixes[i]->getSize();
                if(_direction == Direction::Right)
                {
                    if(_matrixes[0]->getSize().y != currMatrixSize.y)
                        throw "matrixes heights must be equal";

                    size.x += currMatrixSize.x;
                    size.y = currMatrixSize.y;
                }
                else if(_direction == Direction::Down)
                {
                    if(_matrixes[0]->getSize().x != currMatrixSize.x)
                        throw "matrixes widths must be equal";

                    size.x = currMatrixSize.x;
                    size.y += currMatrixSize.y;
                }
            }

            _size = size;
        }

        virtual std::shared_ptr<LedPixel> getPixel(Vector2<uint16_t> position) const override
        {
            for(int i = 0; i < _matrixes.size(); i++)
            {
                LedMatrix* currMatrix = _matrixes[i];
                if(_direction == Direction::Right)
                {
                    uint16_t currMatrixWidth = currMatrix->getSize().x;
                    if(position.x < currMatrixWidth)
                        return currMatrix->getPixel(position);
                    else
                        position.x -= currMatrixWidth;
                }
                else if(_direction == Direction::Down)
                {
                    uint16_t currMatrixHeight = currMatrix->getSize().y;
                    if(position.y < currMatrixHeight)
                        return currMatrix->getPixel(position);
                    else
                        position.y -= currMatrixHeight;
                }
            }

            return nullptr;
        }

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t index) const override
        {
            for(int i = 0; i < _matrixes.size(); i++)
            {
                LedMatrix* currMatrix = _matrixes[i];
                uint16_t currMatrixLength = currMatrix->getLength();
                if(index < currMatrixLength)
                {
                    return currMatrix->getPixel(index);
                }
                else
                {
                    index -= currMatrixLength;
                }
            }

            return nullptr;
        }

        
};
