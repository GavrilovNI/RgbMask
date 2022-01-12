#pragma once

#include <stdint.h>
#include "led/LedMatrix.h"

class MatrixAnimation
{
private:

public:
    virtual void MoveFrame(float delta) = 0;

    virtual void Apply(LedMatrix& matrix) const = 0;
};

