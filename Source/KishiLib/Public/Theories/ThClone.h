#pragma once
#include "Kishi/KishiTheory.h"

/*Clone theory.
requires: copy constructor
impliments: a clone methode*/
template <typename T, TheoryAssumtion TA, typename... bases>
class ThClone
{
private:
    ThClone(){};
};

//stand
template <typename T>
class ThClone<T, TheoryAssumtion::stand> : public Theory<ThClone<T, TheoryAssumtion::stand>>
{
public:
    virtual ~ThClone() = default;
    TUniquePtr<T> Clone_ptr() const
    {
        return TUniquePtr<T>(this->Clone());
    }
    T *Clone() const
    {
        return this->CloneImpl();
    }

protected:
    virtual T *CloneImpl() const
    {
        return new T(THIS);
    }
};

//promise
template <typename T>
class ThClone<T, TheoryAssumtion::promise> : public Theory<ThClone<T, TheoryAssumtion::promise>>
{
public:
    virtual ~ThClone() = default;
    TUniquePtr<T> Clone_ptr() const
    {
        return TUniquePtr<T>(this->Clone());
    }
    T *Clone() const
    {
        return this->CloneImpl();
    }

protected:
    virtual T *CloneImpl() const = 0;
};

//fullfil
template <typename T, typename base>
class ThClone<T, TheoryAssumtion::fullfil, base> : public base
{
protected:
    virtual base *CloneImpl() const
    {
        return new T(THIS);
    }
};
