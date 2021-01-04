#pragma once
#include "Theory/Base/Theory.h"

/*Equal theory.
requires: operator==()
impliments: operator!=()*/
template <typename T, TheoryAssumtion TA, typename... bases>
class ThEquality : public Theory<ThEquality<T, TA, bases...>>, virtual public bases...
{
private:
    ThEquality(){};
};

//stand
template <typename T>
class ThEquality<T, TheoryAssumtion::stand> : public Theory<ThEquality<T, TheoryAssumtion::stand>>
{
    bool Equals(const T &other) const
    {
        return this->operator==(other);
    };
    bool operator!=(const T &other) const
    {
        return !(this->operator==(other));
    };
};
//promise
template <typename T>
class ThEquality<T, TheoryAssumtion::promise> : public Theory<ThEquality<T, TheoryAssumtion::promise>>
{
    bool Equals(const T &other) const
    {
        return this->EqualsImpl(other);
    };
    bool operator!=(const T &other) const
    {
        return !(this->EqualsImpl(other));
    };

protected:
    virtual bool EqualsImpl(const T &one) const = 0;
};
//fullfil
template <typename T, typename base>
class ThEquality<T, TheoryAssumtion::fullfil, base> : virtual public base
{
protected:
    virtual bool EqualsImpl(const base &other) const override
    {
        return (THIS).operator==(other);
    };
};

// template <typename T>
// bool operator==(const TUniquePtr<T> &a, const TUniquePtr<T> &b)
// {
//     return (*a) == (*b);
// };

// template <typename T>
// bool operator!=(const TUniquePtr<T> &a, const TUniquePtr<T> &b)
// {
//     return (*a) != (*b);
// };
