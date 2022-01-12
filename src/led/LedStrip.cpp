#include "LedStrip.h"

LedStrip::LedStrip(uint16_t pixelsCount)
{
    _pixelsCount = pixelsCount;
}

uint16_t LedStrip::getLength() const
{
    return _pixelsCount;
}

void LedStrip::clear()
{
    for(int i = 0; i < getLength(); i++)
    {
        getPixel(i)->clear();
    }
}

std::vector<uint8_t> LedStrip::toBytes() const
{
    std::vector<uint8_t> result;
    uint16_t pixelsCount = getLength();
    for(int i = 0; i < pixelsCount; i++)
    {
        std::vector<uint8_t> pixelBytes = getPixel(i)->toBytes();
        result.insert(result.end(), pixelBytes.begin(), pixelBytes.end());
    }
    return result;
}

void LedStrip::fromBytes(uint8_t* bytes)
{
    uint16_t pixelsCount = getLength();
    for(int i = 0; i < pixelsCount; i++)
    {
        getPixel(i)->fromBytes(bytes + i * 3);
    }
}