#pragma once

#include <stdint.h>

struct ColorHSV;

struct ColorRGB
{
public:
    uint8_t r, g, b;

    ColorRGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0);

    uint32_t toUInt32() const;

    ColorHSV toHSV() const;
    
};

