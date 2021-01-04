#pragma once

#include "KishiAPI.h"
#include "Math.h"
#include "Converts.h"
#include "Data.h"
#include "Motion/Motion.h"
#include <utility>
#include "Kinematics.h"
/*
Kinematic Equations:
(1) S=(U+V)T/2
(2) V=U+AT
(3) S=UT+AT²/2
(4) S=VT-AT²/2
(5) V²=U²+2AS
(5') U²=V²-2AS
 */
#define S GetS()
#define U GetU()
#define V GetV()
#define A GetA()
#define URAISE                                          \
    UE_LOG(LogTemp, Error, TEXT("Unsolveable Motion")); \
    return;

#define H_TFKinematicMotion(T)                                                                                                                                                                                            \
private:                                                                                                                                                                                                                  \
    TMotionFrame<T> start;                                                                                                                                                                                                \
    TMotionFrame<T> end;                                                                                                                                                                                                  \
    float time;                                                                                                                                                                                                           \
                                                                                                                                                                                                                          \
public:                                                                                                                                                                                                                   \
    TFKinematicMotion() = default;                                                                                                                                                                                        \
    CLONEOVERRIDE(TFKinematicMotion)                                                                                                                                                                                      \
    TFKinematicMotion(T s, T u, T v, T a, float t) : TMotionable<T>(), start(T(), u, a), end(s, v, a), time(t){};                                                                                                         \
    TFKinematicMotion(T o, T e, T u, T v, T a, float t) : start(o, u, a), end(e, v, a), time(t){};                                                                                                                        \
    TFKinematicMotion(TMotionFrame<T> start, TMotionFrame<T> end, float time, EKinematicsType _kinematicsType = EKinematicsType::UAT) : TMotionable<T>(), start(start), end(end), time(time) { Solve(_kinematicsType); }; \
    TFKinematicMotion &operator=(const TFKinematicMotion &other) = default;                                                                                                                                               \
    virtual float GetMotionTime() const override { return time; }                                                                                                                                                         \
    FORCEINLINE T GetS() { return end.pos - start.pos; }                                                                                                                                                                  \
    FORCEINLINE T GetU() { return start.vel; }                                                                                                                                                                            \
    FORCEINLINE T GetV() { return end.vel; }                                                                                                                                                                              \
    FORCEINLINE T GetA() { return start.acc; }                                                                                                                                                                            \
    FORCEINLINE float GetT() { return GetMotionTime(); }                                                                                                                                                                  \
                                                                                                                                                                                                                          \
    virtual TMotionFrame<T> GetMotionFrame(float _time) const override                                                                                                                                                     \
    {                                                                                                                                                                                                                     \
        TMotionFrame<T> frame;                                                                                                                                                                                            \
        frame.acc = start.acc;                                                                                                                                                                                            \
        frame.vel = start.vel + (_time * start.acc);                                                                                                                                                                       \
        frame.pos = start.pos + _time * start.vel + (_time * _time / 2) * start.acc;                                                                                                                                         \
        return frame;                                                                                                                                                                                                     \
    };                                                                                                                                                                                                                    \
    void Solve(EKinematicsType _kinematicsType)                                                                                                                                                                           \
    {                                                                                                                                                                                                                     \
        switch (_kinematicsType)                                                                                                                                                                                          \
        {                                                                                                                                                                                                                 \
        case SUV:                                                                                                                                                                                                         \
            SolveAccelerationTime();                                                                                                                                                                                      \
            break;                                                                                                                                                                                                        \
        case SUA:                                                                                                                                                                                                         \
            SolveVelocityTime(false);                                                                                                                                                                                     \
            break;                                                                                                                                                                                                        \
        case SUT:                                                                                                                                                                                                         \
            SolveVelocityAcceleration(false);                                                                                                                                                                             \
            break;                                                                                                                                                                                                        \
        case SVA:                                                                                                                                                                                                         \
            SolveVelocityTime();                                                                                                                                                                                          \
            break;                                                                                                                                                                                                        \
        case SVT:                                                                                                                                                                                                         \
            SolveVelocityAcceleration();                                                                                                                                                                                  \
            break;                                                                                                                                                                                                        \
        case SAT:                                                                                                                                                                                                         \
            SolveVelocityBoth();                                                                                                                                                                                          \
            break;                                                                                                                                                                                                        \
        case UVA:                                                                                                                                                                                                         \
            SolveDistanceTime();                                                                                                                                                                                          \
            break;                                                                                                                                                                                                        \
        case UVT:                                                                                                                                                                                                         \
            SolveDistanceAcceleration();                                                                                                                                                                                  \
            break;                                                                                                                                                                                                        \
        case UAT:                                                                                                                                                                                                         \
            SolveDistanceVelocity(false);                                                                                                                                                                                 \
            break;                                                                                                                                                                                                        \
        case VAT:                                                                                                                                                                                                         \
            SolveDistanceVelocity();                                                                                                                                                                                      \
            break;                                                                                                                                                                                                        \
        default:                                                                                                                                                                                                          \
            break;                                                                                                                                                                                                        \
        }                                                                                                                                                                                                                 \
    };                                                                                                                                                                                                                    \
    void Set(T o, T e, T u, T v, T a, float t)                                                                                                                                                                            \
    {                                                                                                                                                                                                                     \
        start = TMotionFrame<T>(o, u, a);                                                                                                                                                                                 \
        end = TMotionFrame<T>(e, v, a);                                                                                                                                                                                   \
        time = t;                                                                                                                                                                                                         \
    };                                                                                                                                                                                                                    \
    void Set(TMotionFrame<T> _start, TMotionFrame<T> _end, float _time)                                                                                                                                                   \
    {                                                                                                                                                                                                                     \
        this->start = _start;                                                                                                                                                                                             \
        this->end = _end;                                                                                                                                                                                                 \
        this->time = _time;                                                                                                                                                                                               \
    };                                                                                                                                                                                                                    \
    void Subdivide(TFKinematicMotion *TMotion1, TFKinematicMotion *TMotion2, float midTime)                                                                                                                               \
    {                                                                                                                                                                                                                     \
        TMotionFrame<T> mid = GetMotionFrame(midTime);                                                                                                                                                                    \
        TMotion1 = Clone(*this);                                                                                                                                                                                          \
        TMotion1->Set(start, mid, midTime);                                                                                                                                                                               \
        TMotion1 = Clone(*this);                                                                                                                                                                                          \
        TMotion2->Set(mid, end, time - midTime);                                                                                                                                                                          \
    }                                                                                                                                                                                                                     \
    void SubdivideNormalized(TFKinematicMotion &TMotion1, TFKinematicMotion &TMotion2, float midTime) { Subdivide(TMotion1, TMotion2, midTime *time); };

template <typename T>
class TFKinematicMotion : public TMotionable<T>
{
    H_TFKinematicMotion(T)
        //    Kinematic Equations:
        //(1) S=(U+V)T/2
        //(2) V=U+AT
        //(3) S=UT+AT²/2
        //(4) S=VT-AT²/2
        //(5) V²=U²+2AS
        //(5') U²=V²-2AS

        void SolveDistance()
    {
        end.pos = start.pos + (start.vel + end.vel) * time / 2;
    };
    void SolveVelocity(bool InitialVelocity = true)
    {
        if (InitialVelocity)
        {
            start.vel = end.vel - start.acc * time;
        }
        else
        {
            end.vel = start.vel + start.acc * time;
        }
    };
    /* override for quaternions*/
    void SolveAcceleration()
    {
        if (time != 0)
            start.acc = (end.vel - start.vel) / time;
    };

    void SolveTime()
    {
        if (KishiConverts::Kfloat(start.vel + end.vel) != 0)
        {
            time = 2 * KishiConverts::Kfloat(S) / KishiConverts::Kfloat(start.vel + end.vel);
        }
        else
        {
            if (KishiConverts::Kfloat(start.acc) != 0)
            {
                time = KishiConverts::Kfloat(end.vel - start.vel) / KishiConverts::Kfloat(start.acc);
            }
            else
                time = 0;
        }
    };

    void SolveDistanceVelocity(bool InitialVelocity = true)
    {
        if (InitialVelocity)
        {
            end.pos = start.pos + end.vel * time - (start.acc * time * time) / 2;
        }
        else
        {
            end.pos = start.pos + start.vel * time + (start.acc * time * time) / 2;
        }
        SolveVelocity(InitialVelocity);
    };
    void SolveDistanceAcceleration()
    {
        SolveDistance();
        SolveAcceleration();
    };
    /*override for vectors */
    void SolveDistanceTime()
    {
        if (KishiConverts::Kfloat(start.acc) != 0)
        {
            end.pos = start.pos + (pow2(end.vel) - pow2(start.vel)) / (2 * start.acc);
        }
        else
        {
            end.pos = start.pos;
        }
        SolveTime();
    };

    /*override for quaternions */

    void SolveVelocityAcceleration(bool InitialVelocity = true)
    {
        if (time != 0)
        {
            if (InitialVelocity)
            {
                start.vel = 2 * S / time - end.vel;
            }
            else
            {
                end.vel = 2 * S / time - start.vel;
            }
        }
        else
        {
            if (InitialVelocity)
                start.vel = end.vel;
            else
                end.vel = start.vel;
            return;
        }
        SolveAcceleration();
    };
    /*override for quaternions */

    void SolveVelocityBoth()
    {
        start.vel = S / time - start.acc * time / 2;
        end.vel = S / time + start.acc * time / 2;
    };
    /*override for vectors */
    void SolveVelocityTime(bool InitialVelocity = true, bool maxTime = false)
    {
        float U² = pow2(V) - 2 * A * S;
        if (!InitialVelocity)
        {
            //end.vel = 5;
            //time = 6;
            start = -start;
            end = -end;
            UE_LOG(LogTemp, Warning, TEXT("s: %f / %f /%f e: %f / %f /%f t: %f"), start.pos, start.vel, start.acc, end.pos, end.vel, end.acc, time);
            SolveVelocityTime(true, maxTime);
            UE_LOG(LogTemp, Warning, TEXT("s: %f / %f /%f e: %f / %f /%f t: %f"), start.pos, start.vel, start.acc, end.pos, end.vel, end.acc, time);
            start = -start;
            end = -end;
            UE_LOG(LogTemp, Warning, TEXT("s: %f / %f /%f e: %f / %f /%f t: %f"), start.pos, start.vel, start.acc, end.pos, end.vel, end.acc, time);

            return;
        }

        if (U² < 0)
        {
            URAISE;
        }
        start.vel = FMath::Sqrt(U²);
        if (A == 0)
        {
            start.vel = V;
        }
        else if (S == 0 && V == 0)
        {
            start.vel = 0;
        }
        else if ((A <= 0 && S <= 0 && V >= 0) || (A >= 0 && S >= 0 && V <= 0))
        {
            URAISE;
        }
        if (A <= 0 && S >= 0)
        {
            //U is already positive
        }
        else if (A >= 0 && S <= 0)
        {
            start.vel = -start.vel;
        }
        else
        {
            start.vel *= (maxTime ? -1 : 1) * FMath::Sign(V);
        }
        SolveTime();
    };
    /*override for vectors */
    void SolveAccelerationTime()
    {
        if (S != 0)
        {
            start.acc = (pow2(end.vel) - pow2(start.vel)) / (2 * S);
            SolveTime();
        }
        else
        {
            // throw new ArgumentException ();
        }
    };

    //Advanced Solvers
    /*override for vectors */
    void SolveMidPointFixedTime(T midPoint, float midTime = -1)
    {
        if (midTime == -1)
            midTime = KishiConverts::Kfloat(midPoint - start.pos) / KishiConverts::Kfloat((end.pos - midPoint) + (midPoint - start.pos));
        end.pos = start.pos + 2 * (midTime * S - midPoint) / (midTime * (1 - midTime) * pow2(this->time));
        start.vel = (2 * S - start.acc * pow2(time)) / (2 * time);
    };

    void SolveMidPointFixedTimeNormalized(T midPoint, float midTime = -1)
    {
        return SolveInterpolationFixedTime(midPoint, midTime * this->time);
    };
    /*
  returns a second TMotionable that plays after this motion
  override for vectors
   */
    TMotionable<T> *SolveMidPointFixedAcceleration(T midPoint, float midTime = -1)
    {
        if (midTime == -1)
            midTime = (midPoint - start.pos) / KishiConverts::Kfloat((end.pos - midPoint) + (midPoint - start.pos));
        if ((S) == 0)
        {
            return NULL;
        }
        time = (2 * (midTime * S - midPoint)) / (S * midTime * (1 - midTime));
        if (time <= 0)
        {
            TFKinematicMotion m1(start.pos, midPoint, start.vel, T(), T(), 0);
            m1.SolveVelocityTime();
            float t2 = m1.time * ((1 - midTime) * midTime);
            TFKinematicMotion *m2 = (new TFKinematicMotion(midPoint, end.pos, T(), T(), start.acc, t2));
            m2->SolveVelocityBoth();
            time = m1.time;
            *this = m1;
            return m2;
        }
        time = UKismetMathLibrary::Sqrt(time);
        SolveVelocity();
        return NULL;
    };
    /*
  returns a second TMotionable that plays after this motion
  override for vectors
   */
    TMotionable<T> *SolveMidPointFixedInitialVelocity(T midPoint, float midTime = -1)
    {
        if (midTime == -1)
            midTime = (midPoint - start.pos) / KishiConverts::Kfloat((end.pos - midPoint) + (midPoint - start.pos));
        if ((start.vel) == 0)
            return NULL;
        time = (midPoint - midTime * midTime * S) / (midTime * (1 - midTime) * start.vel);
        if (time < 0)
        {
            TFKinematicMotion m1(start.pos, midPoint, start.vel, T(), T(), 0);
            m1.SolveVelocityTime();
            float t2 = m1.time * ((1 - midTime) * midTime);
            TFKinematicMotion *m2 = (new TFKinematicMotion(midPoint, end.pos, T(), T(), start.acc, t2));
            m2->SolveVelocityAcceleration(false);
            time = m1.time;
            *this = m1;
            return m2;
        }
        start.acc = 2 * (midTime * S - midPoint) / (midTime * (1 - midTime) * pow2(time));
        return NULL;
    };
};

#undef S
#undef U
#undef V
#undef A