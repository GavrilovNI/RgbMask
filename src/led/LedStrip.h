#pragma once

#include <cstdint>
#include <vector>
#include <memory>
#include "LedPixel.h"

class LedStrip
{
    private:
        uint16_t _pixelsCount;

    public:
        LedStrip(uint16_t pixelsCount)
        {
            _pixelsCount = pixelsCount;
        }

        uint16_t getLength() const
        {
            return _pixelsCount;
        }

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t index) const = 0;

        void clear()
        {
            for(int i = 0; i < getLength(); i++)
            {
                getPixel(i)->clear();
            }
        }

        std::vector<uint8_t> toBytes() const
        {
            std::vector<uint8_t> result;
            uint16_t pixelsCount = getLength();
            for(int i = 0; i < pixelsCount; i++)
            {
                std::vector<uint8_t> pixelBytes = getPixel(i)->toBytes();
                result.insert(result.end(), pixelBytes.begin(), pixelBytes.end());
            }
            return result;
        }

        void fromBytes(uint8_t* bytes)
        {
            uint16_t pixelsCount = getLength();
            for(int i = 0; i < pixelsCount; i++)
            {
                getPixel(i)->fromBytes(bytes + i * 3);
            }
        }

};
