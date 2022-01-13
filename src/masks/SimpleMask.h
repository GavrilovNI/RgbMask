#pragma once

#include <functional>
#include "Vector2.h"
#include "led/LedMatrix.h"
#include "LedMatrixMask.h"

class SimpleMask : public LedMatrixMask
{
    protected:
        std::function<bool(Vector2<uint16_t>)> _hasPixelFunc;
    public:
        SimpleMask(LedMatrix* ledMatrix, std::function<bool(Vector2<uint16_t>)> hasPixelFunc);

        virtual bool hasPixel(Vector2<uint16_t> position) const override;
};