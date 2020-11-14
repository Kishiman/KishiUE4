#include "MotionableLibrary.h"
#include "Traits.h"

#define CPP_MOTIONABLELIBRARY(T, I, MF, IP)                                                                                   \
    MF UMotionableLibrary::GetStartFrame(const TScriptInterface<I> &object)                                                   \
    {                                                                                                                         \
        return I::Execute_GetMotionFrame(object.GetObject(), 0);                                                              \
    };                                                                                                                        \
    MF UMotionableLibrary::GetEndFrame(const TScriptInterface<I> &object)                                                     \
    {                                                                                                                         \
        return I::Execute_GetMotionFrame(object.GetObject(), I::Execute_GetMotionTime(object.GetObject()));                   \
    };                                                                                                                        \
    MF UMotionableLibrary::GetMotionFrameCapped(const TScriptInterface<I> &object, float time)                                \
    {                                                                                                                         \
        float time_ratio = time / I::Execute_GetMotionTime(object.GetObject());                                               \
        if (time_ratio < 0 || time_ratio > 1)                                                                                 \
            return Zero<float>();                                                                                             \
        return I::Execute_GetMotionFrame(object.GetObject(), time);                                                           \
    };                                                                                                                        \
    MF UMotionableLibrary::GetMotionFrameLooped(const TScriptInterface<I> &object, float time)                                \
    {                                                                                                                         \
        float time_frac = frac(time / I::Execute_GetMotionTime(object.GetObject()));                                          \
        return I::Execute_GetMotionFrame(object.GetObject(), time_frac);                                                      \
    };                                                                                                                        \
    MF UMotionableLibrary::GetMotionFrameInNormalizedTime(const TScriptInterface<I> &object, float normalized_time)           \
    {                                                                                                                         \
        return I::Execute_GetMotionFrame(object.GetObject(), I::Execute_GetMotionTime(object.GetObject()) * normalized_time); \
    }                                                                                                                         \
    MF UMotionableLibrary::GetMotionFrameInNormalizedTimeCapped(const TScriptInterface<I> &object, float normalized_time)     \
    {                                                                                                                         \
        if (normalized_time < 0 || normalized_time > 1)                                                                       \
            return Zero<float>();                                                                                             \
        return GetMotionFrameInNormalizedTime(object, normalized_time);                                                       \
    };                                                                                                                        \
    MF UMotionableLibrary::GetMotionFrameInNormalizedTimeLooped(const TScriptInterface<I> &object, float normalized_time)     \
    {                                                                                                                         \
        float time_frac = frac(normalized_time);                                                                              \
        return GetMotionFrameInNormalizedTime(object, time_frac);                                                             \
    };                                                                                                                        \
    TScriptInterface<I> UMotionableLibrary::Add(const TScriptInterface<I> &left, const TScriptInterface<I> &right)            \
    {                                                                                                                         \
        TMotionable<T> &_left = *new MotionableBPI<T>(left);                                                                  \
        TMotionable<T> &_right = *new MotionableBPI<T>(right);                                                                \
        return IP::NewScript(_left + _right);                                                                                 \
    };                                                                                                                        \
    TScriptInterface<I> UMotionableLibrary::Sub(const TScriptInterface<I> &left, const TScriptInterface<I> &right)            \
    {                                                                                                                         \
        TMotionable<T> &_left = *new MotionableBPI<T>(left);                                                                  \
        TMotionable<T> &_right = *new MotionableBPI<T>(right);                                                                \
        return IP::NewScript(_left - _right);                                                                                 \
    };                                                                                                                        \
    TScriptInterface<I> UMotionableLibrary::Opp(const TScriptInterface<I> &obj)                                               \
    {                                                                                                                         \
        TMotionable<T> &_obj = *new MotionableBPI<T>(obj);                                                                    \
        return IP::NewScript(-_obj);                                                                                          \
    };                                                                                                                        \
    TScriptInterface<I> UMotionableLibrary::Mul(const TScriptInterface<I> &obj, float scale)                                  \
    {                                                                                                                         \
        TMotionable<T> &_obj = *new MotionableBPI<T>(obj);                                                                    \
        return IP::NewScript(_obj * scale);                                                                                   \
    };                                                                                                                        \
    TScriptInterface<I> UMotionableLibrary::Div(const TScriptInterface<I> &obj, float scale)                                  \
    {                                                                                                                         \
        TMotionable<T> &_obj = *new MotionableBPI<T>(obj);                                                                    \
        return IP::NewScript(_obj / scale);                                                                                   \
    };
CPP_MOTIONABLELIBRARY(float, IMotionableF, FMotionFrameF, UMotionableProxyF)