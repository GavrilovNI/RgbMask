#pragma once

#include <cstdint>
#include "LedStrip.h"
#include "Vector2.h"
#include "iostream"

class LedMatrix : public LedStrip
{
    protected:
        Vector2<uint16_t> _size;

    public:
        using LedStrip::getPixel;
        
        LedMatrix(Vector2<uint16_t> size) : LedStrip(size.square())
        {
            _size = size;
        }

        virtual std::shared_ptr<LedPixel> getPixel(Vector2<uint16_t> position) const = 0;


        Vector2<uint16_t> getSize()
        {
            return _size;
        }

        void print()
        {
            String lines;
            for(int y = 0; y < getSize().y; y++)
            {
                String line;
                for(int x = 0; x < getSize().x; x++)
                {
                    auto pixel = getPixel(Vector2<uint16_t>(x, y));
                    line += pixel->toString() + " ";
                }

                lines += line + "\n";
            }
            Serial.print(lines);
        }
};
