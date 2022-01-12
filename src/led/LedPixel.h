#pragma once

#include <cstdint>
#include <vector>
#include "colors/ColorRGB.h"
#include "colors/ColorHSV.h"

class LedPixel
{
    public:
        LedPixel()
        {

        }

        virtual std::vector<uint8_t> toBytes() const = 0;
        virtual void fromBytes(uint8_t* bytes) = 0;

        virtual ColorRGB getColor() const = 0;
        virtual void setColor(const ColorRGB& color) = 0;
        virtual void setColor(const ColorHSV& color) = 0;

        void clear()
        {
            setColor(ColorRGB(0,0,0));
        }
};