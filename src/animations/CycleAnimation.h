#pragma once

#include "Animation.h"

template <typename T>
class CycleAnimation : public Animation<T>
{
protected:
    float _currentTime = 0;
    float _maxTime = 0;
public:

    CycleAnimation(float maxTime)
    {
        _maxTime = maxTime;
    }

    CycleAnimation(float currentTime, float maxTime)
    {
        _currentTime = currentTime;
        _maxTime = maxTime;
    }

    virtual void moveTime(float delta) override
    {
        setCurrentTime(_currentTime + delta);
    }

    float getCurrentTime()
    {
        return _currentTime;
    }

    void setCurrentTime(float currentTime)
    {
        _currentTime = std::fmod(currentTime, _maxTime);
        if(_currentTime < 0)
            _currentTime += _maxTime;
    }

    float getMaxTime()
    {
        return _maxTime;
    }
};

