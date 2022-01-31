#pragma once
#include "colorer/Colorer.h"

template <typename T>
class Animation : public Colorer<T>
{
public:
    virtual void moveTime(float delta) = 0;
};

