#pragma once

#include "tests/MillisTest.h"

#include "led/LedMatrix.h"

#include "animations/Animation.h"
#include "animations/CycleAnimation.h"

class AnimationTest : public MillisTest
{
private:
    std::shared_ptr<CycleAnimation<LedMatrix>> _animation;

  
float speed = 8.0f;

public:

    AnimationTest(std::shared_ptr<AdafruitLedStripContainer<AdafruitLedSnakeMatrix>> ledStrips, std::shared_ptr<LedMatrix> matrix,
                  std::shared_ptr<CycleAnimation<LedMatrix>> animation) : MillisTest(ledStrips, matrix)
    {
        _animation = animation;
    }

    virtual void loop(uint32_t delta) override
    {
        _animation->moveTime(speed * delta / 1000);

        _ledStrips->clear();
        _animation->apply(_matrix);
        _ledStrips->show();
    }
};
