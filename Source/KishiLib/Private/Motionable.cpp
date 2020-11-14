#include "Motionable.h"
#include "Traits.h"

#define CPP_MOTIONABLE(I, MF, IP, ARR)                                                                                                             \
    float IP::GetMotionTime_Implementation() const                                                                                                 \
    {                                                                                                                                              \
        return proxied->GetMotionTime();                                                                                                           \
    };                                                                                                                                             \
    MF IP::GetMotionFrame_Implementation(float time) const                                                                                         \
    {                                                                                                                                              \
        return proxied->GetMotionFrame(time);                                                                                                      \
    };                                                                                                                                             \
                                                                                                                                                   \
    float ARR::GetMotionTime_Implementation() const                                                                                                \
    {                                                                                                                                              \
        float motion_time = 0.0f;                                                                                                                  \
        for (auto motion : motions)                                                                                                                \
        {                                                                                                                                          \
            motion_time += I::Execute_GetMotionTime(motion.GetObject());                                                                           \
        }                                                                                                                                          \
        return motion_time;                                                                                                                        \
    };                                                                                                                                             \
    MF ARR::GetMotionFrame_Implementation(float time) const                                                                                        \
    {                                                                                                                                              \
        float motion_time = 0.0f;                                                                                                                  \
        for (auto motion : motions)                                                                                                                \
        {                                                                                                                                          \
            float tmp = motion_time;                                                                                                               \
            motion_time += I::Execute_GetMotionTime(motion.GetObject());                                                                           \
            if (time <= motion_time)                                                                                                               \
            {                                                                                                                                      \
                return I::Execute_GetMotionFrame(motion.GetObject(), time - tmp);                                                                  \
            }                                                                                                                                      \
        }                                                                                                                                          \
        return I::Execute_GetMotionFrame(motions.Last().GetObject(), time - (motion_time - I::Execute_GetMotionTime(motions.Last().GetObject()))); \
    };
CPP_MOTIONABLE(IMotionableF, FMotionFrameF, UMotionableProxyF, UMotionableArrayF)
CPP_MOTIONABLE(IMotionableFV, FMotionFrameFV, UMotionableProxyFV, UMotionableArrayFV)
