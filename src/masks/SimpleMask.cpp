#include "SimpleMask.h"

SimpleMask::SimpleMask(LedMatrix* ledMatrix, std::function<bool(Vector2<uint16_t>)> hasPixelFunc) : LedMatrixMask(ledMatrix)
{
    _ledMatrix = ledMatrix;
    _hasPixelFunc = hasPixelFunc;
}

bool SimpleMask::hasPixel(Vector2<uint16_t> position) const
{
    return _hasPixelFunc(position);
}