#include "LedMatrix.h"

LedMatrix::LedMatrix(uint16_t width, uint16_t height) : LedStrip(width * height)
{
    _width = width;
    _height = height;
}

uint16_t LedMatrix::getWidth()
{
    return _width;
}

uint16_t LedMatrix::getHeight()
{
    return _height;
}