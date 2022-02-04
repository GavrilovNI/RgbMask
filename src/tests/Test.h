#pragma once

#include "led/adafruit/AdafruitLedStripContainer.h"
#include "led/adafruit/AdafruitLedSnakeMatrix.h"
#include "led/LedMatrix.h"

class Test
{

protected:
    std::shared_ptr<AdafruitLedStripContainer<AdafruitLedSnakeMatrix>> _ledStrips;
    std::shared_ptr<LedMatrix> _matrix;

public:
    Test(std::shared_ptr<AdafruitLedStripContainer<AdafruitLedSnakeMatrix>> ledStrips, std::shared_ptr<LedMatrix> matrix)
    {
        _ledStrips = ledStrips;
        _matrix = matrix;
    }

    virtual void loop() = 0;


};