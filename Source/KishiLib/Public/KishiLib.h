// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "KishiLibDependencies.h"
#include "Kishi/Theory/Base/TheoryInc.h"
#include "Kishi/Math.h"
#include "Kishi/Theory/Base/Theory.h"
#include "Kishi/Expression.h"
#include "Kishi/Data.h"
#include "Kishi/Converts.h"
#include "Kishi/Motion/Motion.h"
#include "Kishi/Motion/FStationaryMotion.h"
#include "Kishi/Motion/FLinearMotion.h"
#include "Kishi/Motion/FKinematicMotion.h"
#include "Kishi/Variable/Variable.h"
class FKishiLibModule : public IModuleInterface
{
public:
  /** IModuleInterface implementation */
  virtual void StartupModule() override;
  virtual void ShutdownModule() override;
};
