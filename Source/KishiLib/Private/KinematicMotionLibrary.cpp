// Fill out your copyright notice in the Description page of Project Settings.
#include "KinematicMotionLibrary.h"
#include "KishiLib.h"

void UKinematicMotion::SolveKM(FMotionFrameF InStart, FMotionFrameF &OutStart, FMotionFrameF InEnd, FMotionFrameF &OutEnd, const float &InTime, float &OutTime, const EKinematicsType _kType)
{
    TFKinematicMotion<float> motion(InStart, InEnd, InTime, _kType);
    OutStart = motion.GetStartFrame();
    OutEnd = motion.GetEndFrame();
    OutTime = motion.GetMotionTime();
};
void UKinematicMotion::PlayMotion(FMotionFrameF InFrame, FMotionFrameF &OutFrame, float time)
{
    TFKinematicMotion<float> motion(InFrame, InFrame, time, EKinematicsType::UAT);
    OutFrame = motion.GetEndFrame();
};
void UKinematicMotion::KinematicMotionable(FMotionFrameF start, FMotionFrameF end, float time, EKinematicsType _kType, TScriptInterface<IMotionableF> &motion)
{
    auto kmotion = new TFKinematicMotion<float>(start, end, time, _kType);
    motion = UMotionableProxyF::NewScript(kmotion);
};


