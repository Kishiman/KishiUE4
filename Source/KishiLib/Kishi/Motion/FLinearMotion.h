#pragma once

#include "CoreMinimal.h"
#include "Math.h"
#include "Kishi/Converts.h"
#include "Kishi/Data.h"
#include "Motion/Motion.h"
#include "Motion/MotionSequence.h"
#include "Motion/MotionOverlay.h"
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
template <typename T>
class TFLinearMotion : virtual public TMotionable<T>
{
    TMotionFrame<T> start;
    float time;

public:
    TFLinearMotion() = default;
    CLONEOVERRIDE(TFLinearMotion)
    TFLinearMotion(T _pos, T _vel, float _time) : start(_pos, _vel), time(_time){};
    TFLinearMotion(TMotionFrame<T> _start, float _time) : start(_start.pos, _start.vel), time(_time){};
    TFLinearMotion(const TMotionable<T> &other) : TFLinearMotion(other.GetStartFrame(), other.GetMotionTime()){};
    TFLinearMotion(TMotionable<T> &&other) : TFLinearMotion(other){};
    virtual float GetMotionTime() const override { return time; };

    virtual TMotionFrame<T> GetMotionFrame(float _time) const override
    {
        T e = start.pos + start.vel * time;
        return TMotionFrame<T>(e, start.vel);
    }
    TFLinearMotion<T> &operator=(const TMotionable<T> &other)
    {
        (*this) = TFLinearMotion(other);
        return *this;
    }
};