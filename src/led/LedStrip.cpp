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
        getPixel(i)->setColor(ColorRGB(0, 0, 0));
    }
}

std::vector<uint8_t> LedStrip::toBytes() const
{
    std::vector<uint8_t> result;
    uint16_t pixelsCount = getLength();
    for(int i = 0; i < pixelsCount; i++)
    {
        std::vector<uint8_t> pixelBytes = getPixel(i)->getColor().toBytes();
        result.insert(result.end(), pixelBytes.begin(), pixelBytes.end());
    }
    return result;
}

void LedStrip::fromBytes(uint8_t* bytes)
{
    uint16_t pixelsCount = getLength();
    for(int i = 0; i < pixelsCount; i++)
    {
        ColorRGB newColor(bytes + i * 3);
        getPixel(i)->setColor(newColor);
    }
}