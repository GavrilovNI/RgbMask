#pragma once

#include <memory>
#include "FooLedPixel.h"
#include "led/LedMatrix.h"

class LedMatrixMask : public LedMatrix
{
    protected:
        LedMatrix* _ledMatrix;
    
    public:
        LedMatrixMask(LedMatrix* ledMatrix) : LedMatrix(ledMatrix->getSize())
        {
            _ledMatrix = ledMatrix;
        }

        virtual bool hasPixel(Vector2<uint16_t> position) const = 0;

        std::shared_ptr<LedPixel> getPixel(uint16_t index) const override
        {
            return _ledMatrix->getPixel(index);
        }

        std::shared_ptr<LedPixel> getPixel(Vector2<uint16_t> position) const override
        {
            if(hasPixel(position))
                return _ledMatrix->getPixel(position);
            else
                return std::make_shared<FooLedPixel>();
        }
};