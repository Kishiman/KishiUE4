#pragma once

#include "CoreMinimal.h"
#include "TMotionFrame.h"
#include <memory>
template <typename T>
// class TMotionable : public IInvertable<TMotionable<T>, false>

class MotionInvert;
template <typename T>
class MotionZero;
template <typename T>
class TMotionOverlay;
template <typename T>
class TMotionSequence;

template <typename T>
class TMotionable : public Expression<TMotionFrame<T>>
{
public:
  DOWNSOLVEOVERRIDE(TMotionable)
  virtual void DownSolve() override
  {
    UE_LOG(LogTemp, Warning, TEXT("OperatorRoot downsolve (%d)"), this);
  };
  EXPRESSION_SYM_BEGIN(TMotionable)
  virtual float GetMotionTime() const override
  {
    return base::express->GetMotionTime();
  };
  virtual TMotionFrame<T> GetMotionFrame(float time) const override
  {
    return base::express->GetMotionFrame(time);
  };
  EXPRESSION_SYM_END()

EXPRESSION_ADD_BEGIN(TMotionable)
  virtual float GetMotionTime() const override
  {
    return fmax(base::a->GetMotionTime(),base::b->GetMotionTime());
  };
  virtual TMotionFrame<T> GetMotionFrame(float time) const override
  {
    return base::a->GetMotionFrame(time)+base::b->GetMotionFrame(time);
  };
EXPRESSION_ADD_END(TMotionable)
EXPRESSION_SUB_BEGIN(TMotionable)
  virtual float GetMotionTime() const override
  {
    return fmax(base::a->GetMotionTime(),base::b->GetMotionTime());
  };
  virtual TMotionFrame<T> GetMotionFrame(float time) const override
  {
    return base::a->GetMotionFrame(time)-base::b->GetMotionFrame(time);
  };
EXPRESSION_SUB_END(TMotionable)
EXPRESSION_OPP_BEGIN(TMotionable)
  virtual float GetMotionTime() const override
  {
    return base::express->GetMotionTime();
  };
  virtual TMotionFrame<T> GetMotionFrame(float time) const override
  {
    return -base::express->GetMotionFrame(time);
  };
EXPRESSION_OPP_END(TMotionable)
EXPRESSION_MUL_BEGIN(TMotionable,float)
  virtual float GetMotionTime() const override
  {
    return base::express->GetMotionTime();
  };
  virtual TMotionFrame<T> GetMotionFrame(float time) const override
  {
    return -base::express->GetMotionFrame(time)*base::a;
  };
EXPRESSION_MUL_END(TMotionable,float)

EXPRESSION_DIV_BEGIN(TMotionable,float)
  virtual float GetMotionTime() const override
  {
    return base::express->GetMotionTime();
  };
  virtual TMotionFrame<T> GetMotionFrame(float time) const override
  {
    return -base::express->GetMotionFrame(time)/base::a;
  };
EXPRESSION_DIV_END(TMotionable,float)
EXPRESSION_SEQ_BEGIN(TMotionable)
  virtual float GetMotionTime() const override
  {
    return base::a->GetMotionTime()+base::b->GetMotionTime();
  };
  virtual TMotionFrame<T> GetMotionFrame(float time) const override
  {
    float time_a=base::a->GetMotionTime();
    return (time<=time_a)?base::a->GetMotionFrame(time):base::b->GetMotionFrame(time-time_a);
  };
EXPRESSION_SEQ_END(TMotionable)
public:
  virtual float GetMotionTime() const = 0;
  virtual TMotionFrame<T> GetMotionFrame(float time) const = 0;
  TMotionFrame<T> operator()(float _time) const { return GetMotionFrame(_time); }
  TMotionable() = default;
  TMotionFrame<T> GetStartFrame() const { return GetMotionFrame(0); }
  TMotionFrame<T> GetEndFrame() const { return GetMotionFrameNormalized(GetMotionTime()); };

  TMotionFrame<T> GetMotionFrameNormalized(float nTime) const
  {
    if (nTime < 0 || nTime > 1)
    {
      return TMotionFrame<T>();
    }
    return GetMotionFrame(nTime * GetMotionTime());
  };
  TMotionable<T> &operator=(const TMotionable<T> &other) = default;
};
template <typename T>
class TMotionableBase : public TMotionable<T>
{
public:
  TMotionableBase() = default;
  CLONEOVERRIDE(TMotionableBase)
  TMotionableBase(Ptr<ThBaseOperatorLV<TMotionFrame<T>, float>> _baseOp, float _time) : baseOp(_baseOp), time(_time){};
  virtual float GetMotionTime() const override { return time; };
  virtual TMotionFrame<T> GetMotionFrame(float _time) const override
  {
    return baseOp->operator()(_time);
  };

private:
  Ptr<ThBaseOperatorLV<TMotionFrame<T>, float>> baseOp;
  float time;
};