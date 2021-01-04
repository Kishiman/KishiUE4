// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Motion/TMotionFrame.h"
#include "MotionFrame.generated.h"
/**
 * 
 */

USTRUCT(BlueprintType)
struct FMotionFrameF
{
  GENERATED_USTRUCT_BODY()
  MOTIONFRAME(FMotionFrameF, float)
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T)
  float pos;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T)
  float vel;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T)
  float acc;
};
USTRUCT(BlueprintType)
struct FMotionFrameFV
{
  GENERATED_USTRUCT_BODY()
  MOTIONFRAME(FMotionFrameFV, FVector)
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T)
  FVector pos;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T)
  FVector vel;
  UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T)
  FVector acc;
};
USTRUCT(BlueprintType)
struct FMotionFrameTR
{
  GENERATED_USTRUCT_BODY()
  //TODO
};
// using FMotionFrame<FTrandform>=FMotionFrameFV;
