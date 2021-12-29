#pragma once

#include <cstdint>
#include <Adafruit_NeoPixel.h>
#include "LedStrip.h"

class LedPixel
{
    private:
        uint8_t* _pixel;
        const uint8_t& _rOffset;
        const uint8_t& _gOffset;
        const uint8_t& _bOffset;
        const uint8_t& _wOffset;
        const uint8_t& _brightness;

    public:
        LedPixel(uint8_t *pixel, const uint8_t& rOffset, const uint8_t& gOffset, const uint8_t& bOffset, const uint8_t& wOffset, const uint8_t& brightness)
            :_pixel(pixel), _rOffset(rOffset), _gOffset(gOffset), _bOffset(bOffset), _wOffset(wOffset), _brightness(brightness)
        {

        }

        uint32_t GetColor()
        {
            uint8_t r = _pixel[_rOffset];
            uint8_t g = _pixel[_gOffset];
            uint8_t b = _pixel[_rOffset];
            uint32_t color = (((uint32_t)r) << 16) + (((uint32_t)g) << 8) + b;
            return color;
        }

        void SetColor(uint32_t color)
        {
            uint8_t r = (uint8_t)(color >> 16);
            uint8_t g = (uint8_t)(color >> 8);
            uint8_t b = (uint8_t)(color);
            SetColor(r, g, b);
        }

        void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
        {
            if (_brightness) { // See notes in setBrightness()
                w = (w * _brightness) >> 8;
            }
            SetColor(r, g, b);
            _pixel[_wOffset] = w;
        }

        void SetColor(uint8_t r, uint8_t g, uint8_t b)
        {
            if (_brightness) { // See notes in setBrightness()
                r = (r * _brightness) >> 8;
                g = (g * _brightness) >> 8;
                b = (b * _brightness) >> 8;
            }
            _pixel[_rOffset] = r;
            _pixel[_gOffset] = g;
            _pixel[_bOffset] = b;
        }

};