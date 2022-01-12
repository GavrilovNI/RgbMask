#pragma once

#include <vector>
#include <functional>
#include <Adafruit_NeoPixel.h>
#include "led/adafruit/AdafruitLedStrip.h"

template<typename T, typename std::enable_if<std::is_base_of<Adafruit_NeoPixel, T>::value>::type* = nullptr>
class AdafruitLedStripContainer
{
    public:
        std::vector<T*> strips;

        AdafruitLedStripContainer()
        {
        }

        AdafruitLedStripContainer(std::vector<T*> strips)
        {
            this->strips = strips;
        }
        

        void push_back(T* strip)
        {
            strips.push_back(strip);
        }
        
        void apply(std::function<void(T*)> func)
        {
            for(auto strip : strips)
            {
                func(strip);
            }
        }


        void begin()
        {
            apply([](T* strip)
                {
                    strip->Adafruit_NeoPixel::begin();
                }
            );
        }
        
        void show()
        {
            apply([](T* strip)
                {
                    strip->Adafruit_NeoPixel::show();
                }
            );
        }

        void setBrightness(uint8_t value)
        {
            apply([&value](T* strip)
                {
                    strip->Adafruit_NeoPixel::setBrightness(value);
                }
            );
        }

        void clear()
        {
            apply([](T* strip)
                {
                    strip->Adafruit_NeoPixel::clear();
                }
            );
        }
};

