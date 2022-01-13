#pragma once

#include "led/LedPixel.h"

class FooLedPixel : public LedPixel
{
    public:
        ColorRGB getColor() const
        {
            return ColorRGB(0, 0, 0);
        }
        void setColor(const ColorRGB& color)
        {

        }
        void setColor(const ColorHSV& color)
        {
            
        }
};

