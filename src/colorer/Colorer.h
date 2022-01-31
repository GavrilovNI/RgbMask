#pragma once
#include <memory>

template <typename T>
class Colorer
{
public:
    virtual void apply(std::shared_ptr<T> object) const = 0;
};