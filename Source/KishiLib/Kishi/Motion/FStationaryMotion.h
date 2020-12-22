#pragma once

#include "CoreMinimal.h"
#include "Math.h"
#include "Kishi/Converts.h"
#include "Kishi/Data.h"
#include "Motion/Motion.h"
#include "Motion/MotionSequence.h"
#include <utility>

/*
Kinematic Equations:
(1) S=(U+V)T/2
(2) V=U+AT
(3) S=UT+AT²/2
(4) S=VT-AT²/2
(5) V²=U²+2AS
(5') U²=V²-2AS
 */
static int instances;
template <typename T>
class TFStationaryMotion : public TMotionable<T> // public ThAdd<TFStationaryMotion<T>, TheoryAssumtion::fullfil, TMotionable<T>>
{
    T pos;
    float time;

public:
    //static int instances;

    TFStationaryMotion()= default;
    CLONEOVERRIDE(TFStationaryMotion)
    TFStationaryMotion(T _pos, float _time) : TMotionable<T>(), pos(_pos), time(_time){};
    TFStationaryMotion(TMotionFrame<T> _start, float _time) : pos(_start.pos), time(_time){};
    TFStationaryMotion(const TMotionable<T> &other)
    {
        *this = other;
    };
    TFStationaryMotion(TMotionable<T> &&other)
    {
        *this = other;
    };
    virtual float GetMotionTime() const override
    {
        return time;
    }
    virtual TMotionFrame<T> GetMotionFrame
(float _time) const override
    {
        return TMotionFrame<T>(pos);
    }
    virtual TFStationaryMotion<T> &operator=(const TMotionable<T> &other)
    {
        this->pos = other.GetStartFrame().pos;
        this->time = other.GetMotionTime();
        return *this;
    }
};