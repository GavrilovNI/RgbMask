
#include <algorithm>
#include "LedMatrixMask.h"
#include "SimpleMask.h"
#include "BrightnessLedPixel.h"

LedMatrixMask::LedMatrixMask(std::shared_ptr<LedMatrix> ledMatrix) : LedMatrix(ledMatrix->getSize())
{
    _ledMatrix = ledMatrix;
}

std::shared_ptr<LedPixel> LedMatrixMask::getPixel(uint16_t index) const
{
    return _ledMatrix->getPixel(index);
}

std::shared_ptr<LedPixel> LedMatrixMask::getPixel(Vector2<uint16_t> position) const
{
    auto pixel = _ledMatrix->getPixel(position);
    auto brightness = getPixelBrightness(position);

    return std::make_shared<BrightnessLedPixel>(pixel, brightness);
}

std::shared_ptr<LedMatrixMask> LedMatrixMask::invert()
{
    return std::make_shared<SimpleMask>(_ledMatrix, [&](Vector2<uint16_t> position)
        {
            return 255 - this->getPixelBrightness(position);
        });
}

std::shared_ptr<LedMatrixMask> LedMatrixMask::max_(std::shared_ptr<LedMatrixMask> mask)
{
    return std::make_shared<SimpleMask>(_ledMatrix, [&, mask](Vector2<uint16_t> position)
        {
            return std::max(this->getPixelBrightness(position), mask->getPixelBrightness(position));
        });
}

std::shared_ptr<LedMatrixMask> LedMatrixMask::min_(std::shared_ptr<LedMatrixMask> mask)
{
    return std::make_shared<SimpleMask>(_ledMatrix, [&, mask](Vector2<uint16_t> position)
        {
            return std::min(this->getPixelBrightness(position), mask->getPixelBrightness(position));
        });
}