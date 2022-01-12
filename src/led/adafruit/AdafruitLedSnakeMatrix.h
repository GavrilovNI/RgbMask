#pragma once

#include <cstdint>
#include <Adafruit_NeoPixel.h>
#include "led/LedSnakeMatrix.h"

class AdafruitLedSnakeMatrix : public LedSnakeMatrix, public Adafruit_NeoPixel
{
    public:
        AdafruitLedSnakeMatrix(uint16_t width, uint16_t height, int16_t pin = 6, neoPixelType type = NEO_GRB + NEO_KHZ800)
            : LedSnakeMatrix(width, height), Adafruit_NeoPixel(width * height, pin, type)
        {
        }
};
