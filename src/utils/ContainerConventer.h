#pragma once


template<class SourceContainer>
class ContainerConverter
{
    const SourceContainer& s_;
public:
    explicit ContainerConverter(const SourceContainer& s) : s_(s) {}

    template<class TargetContainer>
    operator TargetContainer() const
    {
        return TargetContainer(s_.begin(), s_.end());
    }
};

template<class C>
ContainerConverter<C> container_cast(const C& c)
{
    return ContainerConverter<C>(c);
}
