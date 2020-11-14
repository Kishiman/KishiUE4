// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KishiLibDependencies.h"
#include "Theories/Theories.h"
#include "Kishi/KishiMath.h"
#include "Kishi/KishiTheory.h"
#include "Kishi/KishiData.h"
#include "Kishi/KishiConverts.h"
#include "Motion/Motion.h"
#include "Motion/FStationaryMotion.h"
#include "Motion/FLinearMotion.h"
#include "Motion/FKinematicMotion.h"
#include "Variable/Variable.h"
class FKishiLibModule : public IModuleInterface
{
public:
  /** IModuleInterface implementation */
  virtual void StartupModule() override;
  virtual void ShutdownModule() override;
};
