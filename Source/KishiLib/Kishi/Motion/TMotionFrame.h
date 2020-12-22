#pragma once

#include "CoreMinimal.h"
#include "Kishi/Theory/Base/TheoryInc.h"
// #include "TMotionFrame.generated.h"

template <typename T>
//USTRUCT(BlueprintType)
struct TMotionFrame //public ThAdd<TMotionFrame<T>, TheoryAssumtion::fullfil>
{
public:
  //UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T)
  T pos;
  // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T)
  T vel;
  // UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = T)
  T acc;
  TMotionFrame() = default;
  TMotionFrame(const TMotionFrame &other) = default;
  TMotionFrame(T pos, T vel = T(), T acc = T()) : pos(pos), vel(vel), acc(acc){};
  // UFUNCTION(BlueprintPure, Category = T)
  TMotionFrame operator+(const TMotionFrame &other)
  {
    return TMotionFrame(pos + other.pos, vel + other.vel, acc + other.acc);
  }
  // UFUNCTION(BlueprintPure, Category = T)
  TMotionFrame operator-() const
  {
    return TMotionFrame(pos, -vel, acc);
  }
  // UFUNCTION(BlueprintPure, Category = T)
  TMotionFrame operator-(const TMotionFrame &other) const
  {
    return TMotionFrame(pos - other.pos, vel - other.vel, acc - other.acc);
  }
  // UFUNCTION(BlueprintPure, Category = T)
  TMotionFrame operator*(const float scale) const
  {
    return TMotionFrame(pos * scale, vel * scale, acc * scale);
  }
  // UFUNCTION(BlueprintPure, Category = T)
  TMotionFrame operator/(const float scale) const
  {
    return TMotionFrame(pos / scale, vel / scale, acc / scale);
  }

  operator TArray<T>()
  {
    T array[3] = {pos, vel, acc};
    return TArray<T>(array, 3);
  }
};
#define MOTIONFRAME(S, T)                                                          \
  S() = default;                                                                   \
  S(const S &other) = default;                                                     \
  S(T pos, T vel = T(), T acc = T()) : pos(pos), vel(vel), acc(acc){};             \
  S(TMotionFrame<T> tmf) : pos(tmf.pos), vel(tmf.vel), acc(tmf.acc){};             \
  S operator+(S other)                                                          \
  {                                                                                \
    return S(this->pos + other.pos, this->vel + other.vel, this->acc + other.acc); \
  };                                                                               \
  S operator-(S other)                                                          \
  {                                                                                \
    return S(this->pos - other.pos, this->vel - other.vel, this->acc - other.acc); \
  };                                                                               \
  S operator-()                                                                 \
  {                                                                                \
    return S(-this->pos, -this->vel, -this->acc);                                  \
  };                                                                               \
  S operator*(float scale)                                                      \
  {                                                                                \
    return S(this->pos * scale, this->vel * scale, this->acc * scale);             \
  };                                                                               \
  operator TMotionFrame<T>() const                                                 \
  {                                                                                \
    TMotionFrame<T> mf = {pos, vel, acc};                                          \
    return mf;                                                                     \
  };                                                                               \
  operator TArray<T>()                                                             \
  {                                                                                \
    T array[3] = {pos, vel, acc};                                                  \
    return TArray<T>(array, 3);                                                    \
  };