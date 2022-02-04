#pragma once

#include "tests/Test.h"

class MillisTest : public Test
{
private:
    uint32_t _loopDelay;
    uint32_t _lastMillis;

public:
    MillisTest(std::shared_ptr<AdafruitLedStripContainer<AdafruitLedSnakeMatrix>> ledStrips, std::shared_ptr<LedMatrix> matrix, uint32_t loopDelay = 10) : Test(ledStrips, matrix)
    {
        _loopDelay = loopDelay;
        _lastMillis = millis();
    }

    virtual void loop(uint32_t delta) = 0;

    virtual void loop() override final
    {
        uint32_t currMillis = millis();
        uint32_t delta = currMillis - _lastMillis;
        _lastMillis = currMillis;

        loop(delta);

        delay(_loopDelay);
    }
};