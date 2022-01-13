#pragma once

#include <stdint.h>
#include <vector>

struct ColorHSV;

struct ColorRGB
{
public:
    uint8_t r, g, b;

    ColorRGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0);
    ColorRGB(uint8_t* bytes);

    uint32_t toUInt32() const;

    ColorHSV toHSV() const;

    std::vector<uint8_t> toBytes() const;
    
};

