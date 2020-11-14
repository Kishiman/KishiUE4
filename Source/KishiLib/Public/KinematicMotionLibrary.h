// Fill your out opyright notice in the Description page of Project Settings.

#pragma once

#include "KishiLib.h"
#include "Kinematics.h"
#include "MotionFrame.h"
#include "MotionableLibrary.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KinematicMotionLibrary.generated.h"

UCLASS()
class KISHILIB_API UKinematicMotion : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
//float
	UFUNCTION(BlueprintPure, category = float)
	static void PlayMotion(FMotionFrameF InFrame,FMotionFrameF &OutFrame,float time);
	UFUNCTION(BlueprintPure, category = float)
	static void SolveKM(FMotionFrameF InStart,FMotionFrameF &OutStart,FMotionFrameF InEnd,FMotionFrameF &OutEnd,const float &InTime,float &OutTime,const EKinematicsType _kType);
	UFUNCTION(BlueprintPure, category = float)
	static void KinematicMotionable(FMotionFrameF start,FMotionFrameF end,float time,EKinematicsType _kType,TScriptInterface<IMotionableF>& motion);
	
	
};
