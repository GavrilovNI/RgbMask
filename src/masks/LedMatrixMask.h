#pragma once

#include <memory>
#include "FooLedPixel.h"
#include "led/LedMatrix.h"


class LedMatrixMask : public LedMatrix
{
    protected:
        LedMatrix* _ledMatrix;
    
    public:
        LedMatrixMask(LedMatrix* ledMatrix);

        virtual bool hasPixel(Vector2<uint16_t> position) const = 0;

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t index) const override;

        virtual std::shared_ptr<LedPixel> getPixel(Vector2<uint16_t> position) const override;

        std::shared_ptr<LedMatrixMask> invert();
        std::shared_ptr<LedMatrixMask> and_(std::shared_ptr<LedMatrixMask> mask);
        std::shared_ptr<LedMatrixMask> or_(std::shared_ptr<LedMatrixMask> mask);
        std::shared_ptr<LedMatrixMask> xor_(std::shared_ptr<LedMatrixMask> mask);
};
