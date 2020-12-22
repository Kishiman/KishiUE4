#pragma once

#include "CoreMinimal.h"
#include "Motion/Motion.h"
#include "Kishi/Data.h"
template <typename T>
class TMotionSequence : public TMotionable<T> // public  ThAdd<MotionInvert<T>, TheoryAssumtion::fullfil, TMotionable<T>>
{

private:
    TArray<const TMotionable<T>> motions;
public:
    //Constructors
    CLONEOVERRIDE(TMotionSequence)
    TMotionSequence(TArray<const TMotionable<T>> _motions) : motions(_motions){};
    float GetMotionTime() const override
    {
        float time_acc=0;
        for(auto& motion:motions){
            time_acc+=motion.GetMotionTime();
        }
        return time_acc;
    };
    virtual TMotionFrame<T> GetMotionFrame(float _time) const override
    {
        float time_acc=0;
        for(auto& motion:motions){
            float tmp=time_acc;
            time_acc+=motion->GetMotionTime();
            if(_time<=time_acc){return motion->GetMotionFrame(_time-tmp); }
        }
        return motions[0]->GetMotionFrame(_time);
    };
};
