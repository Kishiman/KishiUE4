#pragma once

#include "KishiAPI.h"

class KishiConverts
{
public:
FORCEINLINE static const float Kfloat(float floa) { return floa; };
FORCEINLINE static const float Kfloat(FVector vect) { return vect.Size(); };
FORCEINLINE static const float Kfloat(FVector2D vect) { return vect.Size(); };
FORCEINLINE static const float Kfloat(FVector4 vect) { return vect.Size(); };
FORCEINLINE static const float Kfloat(FQuat quat) { return quat.GetAngle(); };
};


