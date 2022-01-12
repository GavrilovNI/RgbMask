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
        LedStrip(uint16_t pixelsCount);

        uint16_t getLength() const;

        virtual std::shared_ptr<LedPixel> getPixel(uint16_t index) const = 0;

        void clear();

        std::vector<uint8_t> toBytes() const;

        void fromBytes(uint8_t* bytes);

};
