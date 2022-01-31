#pragma once

#include <memory>
#include "led/LedMatrix.h"


class LedMatrixMask : public LedMatrix
{
    protected:
        std::shared_ptr<LedMatrix> _ledMatrix;
    
    public:
        LedMatrixMask(std::shared_ptr<LedMatrix> ledMatrix);

        virtual uint8_t getPixelBrightness(Vector2<uint16_t> position) const = 0;

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t index) const override;

        virtual std::shared_ptr<LedPixel> getPixel(Vector2<uint16_t> position) const override;

        std::shared_ptr<LedMatrixMask> invert();
        std::shared_ptr<LedMatrixMask> max_(std::shared_ptr<LedMatrixMask> mask);
        std::shared_ptr<LedMatrixMask> min_(std::shared_ptr<LedMatrixMask> mask);
};
