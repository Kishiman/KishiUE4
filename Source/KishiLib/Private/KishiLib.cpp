// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "KishiLib.h"

#define LOCTEXT_NAMESPACE "FKishiLibModule"

Ptr<ThBaseOperatorLV<int, float>> GetSymbol()
{
  using Sym = ThBaseOperatorLV<int, float>::Sym;
  using Dyn = ThBaseOperatorLV<int, float>::Dyn;

  Sym _floor(new Dyn([](float x){return floor(x);}));
  Sym _ceil(new Dyn([](float x){return ceil(x);}));
  Sym res = (_ceil + _floor);
  return res.Clone();
}
void TestTheory()
{
  using Sym = ThBaseOperatorLV<int, float>::Sym;
  using Dyn = ThBaseOperatorLV<int, float>::Dyn;
  ThBaseOperatorLV<int>::Dyn one([](){return 1;});
  ThBaseOperatorLV<int>::Dyn two([](){return 2;});
  ThBaseOperatorLV<int>::Dyn three([](){return 3;});
  ThBaseOperatorLV<float,int>::Dyn intTofloat([](int x){return (float)(x);});
  ThBaseOperatorLV<float, void>::Sym symbol = 7 * intTofloat.op(one + two + three);
  UE_LOG(LogTemp, Warning, TEXT("(1+2+3)*7=42=%f"), symbol());
  Dyn _floor([](float f) { return floor(f); });
  Dyn _ceil([](float f) { return ceil(f); });
  ThBaseOperatorLV<float, float>::Dyn _power2([](float f) { return powf(f, 2); });
  Sym res = _floor.op(_power2 + _power2) + _ceil;
  for (int i = 0; i < 10; i++)
  {
    float result = res(0.7 * (float)i);
    UE_LOG(LogTemp, Warning, TEXT("(floor(power2 + power2)+ceil)(%f)=%f"), 0.7 * (float)(i), result);
  }
  Sym x = GetSymbol();
  Sym a = x + _ceil;
  ThBaseOperatorLV<float, int>::Sym half(new Dyn([](int x){return x+0.5f;}));
  ThBaseOperatorLV<float, float>::Sym d = half.op(a);
  for (int i = 0; i < 10; i++)
  {
    float result = d(0.7 * (float)i);
    UE_LOG(LogTemp, Warning, TEXT("half(floor + ceil) (%f)=%f"), 0.7 * (float)(i), result);
  }
};
void FKishiLibModule::StartupModule()
{
  UE_LOG(LogTemp, Warning, TEXT("KishiLib On"));
  TestTheory();
  UE_LOG(LogTemp, Warning, TEXT("Tested Theory"));
  using Symf = TMotionable<float>::Sym;
  using SymV = TMotionable<FVector>::Sym;
  TMotionFrame<float> startF(0, 3, 0);
  TMotionFrame<float> endF(2, -1, 0);
  TFKinematicMotion<float> a(startF, endF, 10);
  TFKinematicMotion<float>::Sym b = -a;
  TFKinematicMotion<float>::Sym c = a + a;
  for (int i = 0; i < 11; ++i)
  {
    UE_LOG(LogTemp, Warning, TEXT(" (%d):a= %f,-a= %f,(a+a)= %f"), i, a(i).pos, b(i).pos, c(i).pos);
  }
  // This code will execute after your module is loaded into memory; the exact
  // timing is specified in the .uplugin file per-module
}

void FKishiLibModule::ShutdownModule()
{
  UE_LOG(LogTemp, Warning, TEXT("KishiLib Off"));

  // This function may be called during shutdown to clean up your module.  For
  // modules that support dynamic reloading, we call this function before
  // unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FKishiLibModule, KishiLib)