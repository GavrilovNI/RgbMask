#include "LedMatrixMask.h"
#include "SimpleMask.h"

LedMatrixMask::LedMatrixMask(LedMatrix* ledMatrix) : LedMatrix(ledMatrix->getSize())
{
    _ledMatrix = ledMatrix;
}

std::shared_ptr<LedPixel> LedMatrixMask::getPixel(uint16_t index) const
{
    return _ledMatrix->getPixel(index);
}

std::shared_ptr<LedPixel> LedMatrixMask::getPixel(Vector2<uint16_t> position) const
{
    if(hasPixel(position))
        return _ledMatrix->getPixel(position);
    else
        return std::make_shared<FooLedPixel>();
}

std::shared_ptr<LedMatrixMask> LedMatrixMask::invert()
{
    return std::make_shared<SimpleMask>(_ledMatrix, [&](Vector2<uint16_t> position)
        {
            return !this->hasPixel(position);
        });
}

std::shared_ptr<LedMatrixMask> LedMatrixMask::and_(std::shared_ptr<LedMatrixMask> mask)
{
    return std::make_shared<SimpleMask>(_ledMatrix, [&, mask](Vector2<uint16_t> position)
        {
            return this->hasPixel(position) && mask->hasPixel(position);
        });
}

std::shared_ptr<LedMatrixMask> LedMatrixMask::or_(std::shared_ptr<LedMatrixMask> mask)
{
    return std::make_shared<SimpleMask>(_ledMatrix, [&, mask](Vector2<uint16_t> position)
        {
            return this->hasPixel(position) || mask->hasPixel(position);
        });
}

std::shared_ptr<LedMatrixMask> LedMatrixMask::xor_(std::shared_ptr<LedMatrixMask> mask)
{
    return std::make_shared<SimpleMask>(_ledMatrix, [&, mask](Vector2<uint16_t> position)
        {
            return this->hasPixel(position) != mask->hasPixel(position);
        });
}