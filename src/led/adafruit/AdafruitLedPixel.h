#pragma once

#include <cstdint>
#include <Adafruit_NeoPixel.h>
#include <vector>
#include "led/LedPixel.h"
#include "AdafruitLedStrip.h"
#include "colors/ColorRGB.h"

class AdafruitLedPixel : LedPixel
{
    private:
        uint8_t* _pixel;
        const uint8_t& _rOffset;
        const uint8_t& _gOffset;
        const uint8_t& _bOffset;
        const uint8_t& _wOffset;
        const uint8_t& _brightness;

    public:
        AdafruitLedPixel(uint8_t *pixel, const uint8_t& rOffset, const uint8_t& gOffset, const uint8_t& bOffset, const uint8_t& wOffset, const uint8_t& brightness)
            :_pixel(pixel), _rOffset(rOffset), _gOffset(gOffset), _bOffset(bOffset), _wOffset(wOffset), _brightness(brightness)
        {

        }

        std::vector<uint8_t> toBytes() const override
        {
            return std::vector<uint8_t> { _pixel[_rOffset], _pixel[_gOffset], _pixel[_bOffset] };
        }

        void fromBytes(uint8_t* bytes)
        {
            setColor(bytes[0], bytes[1], bytes[2]);
        }

        ColorRGB getColor() const override
        {
            uint8_t r = _pixel[_rOffset];
            uint8_t g = _pixel[_gOffset];
            uint8_t b = _pixel[_rOffset];
            return ColorRGB(r, g, b);
        }

        void setColor(const ColorRGB& color) override
        {
            setColor(color.r, color.g, color.b);
        }

        void setColor(const ColorHSV& color) override
        {
            setColor(color.toRGB());
        }

        void setColor(uint32_t color)
        {
            uint8_t r = (uint8_t)(color >> 16);
            uint8_t g = (uint8_t)(color >> 8);
            uint8_t b = (uint8_t)(color);
            setColor(r, g, b);
        }

        void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
        {
            if (_brightness) { // See notes in setBrightness()
                w = (w * _brightness) >> 8;
            }
            setColor(r, g, b);
            _pixel[_wOffset] = w;
        }

        void setColor(uint8_t r, uint8_t g, uint8_t b)
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