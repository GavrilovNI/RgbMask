#pragma once

#include <functional>
#include "Vector2.h"
#include "led/LedMatrix.h"
#include "LedMatrixMask.h"

class SimpleMask : public LedMatrixMask
{
    protected:
        std::function<uint8_t(Vector2<uint16_t>)> _getPixelBrightnessFunc;
    public:
        SimpleMask(std::shared_ptr<LedMatrix> ledMatrix, std::function<uint8_t(Vector2<uint16_t>)> getPixelBrightnessFunc) : LedMatrixMask(ledMatrix)
        {
            _getPixelBrightnessFunc = getPixelBrightnessFunc;
        }

        virtual uint8_t getPixelBrightness(Vector2<uint16_t> position) const override
        {
            return _getPixelBrightnessFunc(position);
        }
};