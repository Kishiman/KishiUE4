#pragma once

#include "KishiAPI.h"
#include "Motion/Motion.h"
#include "Data.h"
#include "Math.h"

template <typename T>
class TMotionOverlay : public TMotionable<T>
{
private:
    const TMotionable<T> &first;
    const TMotionable<T> &second;

public:
    //Constructors
    TMotionOverlay(const TMotionable<T> &a, const TMotionable<T> &b) : first(a), second(b){};
    CLONEOVERRIDE(TMotionOverlay)
    float GetMotionTime() const //override
    {
        return FMath::Max(first.GetMotionTime(), second.GetMotionTime());
    }
    TMotionFrame<T> GetMotionFrame
(float time) const //override
    {
        if (time < 0 || time > GetMotionTime())
            return TMotionFrame<T>();
        return first.GetMotionFrame
(time) + second.GetMotionFrame
(time);
    }
};
