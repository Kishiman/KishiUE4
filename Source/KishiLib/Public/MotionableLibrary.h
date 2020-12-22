#pragma once
#include "KishiLib.h"
#include "Kishi/Motion/Kinematics.h"
#include "MotionFrame.h"
#include "Motionable.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MotionableLibrary.generated.h"
UCLASS()
class KISHILIB_API UMotionableLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintPure, Category = "Default")
    static FMotionFrameF GetStartFrame(const TScriptInterface<IMotionableF> &object);
    UFUNCTION(BlueprintPure, Category = "Default")
    static FMotionFrameF GetEndFrame(const TScriptInterface<IMotionableF> &object);
    UFUNCTION(BlueprintPure, Category = "Default")
    static FMotionFrameF GetMotionFrameCapped(const TScriptInterface<IMotionableF> &object, float time);
    UFUNCTION(BlueprintPure, Category = "Default")
    static FMotionFrameF GetMotionFrameLooped(const TScriptInterface<IMotionableF> &object, float time);
    UFUNCTION(BlueprintPure, Category = "Default")
    static FMotionFrameF GetMotionFrameInNormalizedTime(const TScriptInterface<IMotionableF> &object, float normalized_time);
    UFUNCTION(BlueprintPure, Category = "Default")
    static FMotionFrameF GetMotionFrameInNormalizedTimeCapped(const TScriptInterface<IMotionableF> &object, float normalized_time);
    UFUNCTION(BlueprintPure, Category = "Default")
    static FMotionFrameF GetMotionFrameInNormalizedTimeLooped(const TScriptInterface<IMotionableF> &object, float normalized_time);
    UFUNCTION(BlueprintPure, Category = "Motion")
    static TScriptInterface<IMotionableF> Add(const TScriptInterface<IMotionableF> &left, const TScriptInterface<IMotionableF> &right);
    UFUNCTION(BlueprintPure, Category = "Motion")
    static TScriptInterface<IMotionableF> Sub(const TScriptInterface<IMotionableF> &left, const TScriptInterface<IMotionableF> &right);
    UFUNCTION(BlueprintPure, Category = "Motion")
    static TScriptInterface<IMotionableF> Opp(const TScriptInterface<IMotionableF> &obj);
    UFUNCTION(BlueprintPure, Category = "Motion")
    static TScriptInterface<IMotionableF> Mul(const TScriptInterface<IMotionableF> &obj, float scale);
    UFUNCTION(BlueprintPure, Category = "Motion")
    static TScriptInterface<IMotionableF> Div(const TScriptInterface<IMotionableF> &obj, float scale);
};
//*************************************MACROS*************************************
