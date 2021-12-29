#pragma once

#include <stdint.h>
#include "LedSnakeMatrix.h"

class Animation
{
private:

public:
    virtual void MoveFrame(float delta) = 0;

    virtual void Apply(LedSnakeMatrix& matrix) = 0;
};

