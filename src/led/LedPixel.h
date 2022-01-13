#pragma once

#include <cstdint>
#include <vector>
#include "colors/ColorRGB.h"
#include "colors/ColorHSV.h"

class LedPixel
{
    public:
        virtual ColorRGB getColor() const = 0;
        virtual void setColor(const ColorRGB& color) = 0;
        virtual void setColor(const ColorHSV& color) = 0;
};