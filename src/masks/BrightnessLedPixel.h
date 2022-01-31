#pragma once

#include <memory>
#include "led/LedPixel.h"

class BrightnessLedPixel : public LedPixel
{
    protected:
        std::shared_ptr<LedPixel> _pixel;
        float _brightness;
        
    public:
        BrightnessLedPixel(std::shared_ptr<LedPixel> pixel, uint8_t brightness)
        {
            _pixel = pixel;
            _brightness = brightness / 255.0;
        }

        ColorRGB getColor() const
        {
            return _pixel->getColor();
        }
        void setColor(const ColorRGB& color)
        {
            setColor(color.toHSV());
        }
        void setColor(const ColorHSV& color)
        {
            ColorHSV newValue = color;
            float brightness = color.getV();
            brightness = brightness * _brightness;
            newValue.setV(brightness);
            _pixel->setColor(newValue);
        }
};

