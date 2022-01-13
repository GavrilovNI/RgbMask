#pragma once

template <typename T>
class Animation
{
public:
    virtual void moveTime(float delta) = 0;

    virtual void apply(std::shared_ptr<T> object) const = 0;
};

