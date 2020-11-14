// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MotionFrame.h"
#include "Motion/Motion.h"
#include "Traits.h"
#include "Motionable.generated.h"
// This class does not need to be modified.
template <typename T>
struct Motionable
{
	typedef void I;
	typedef void MF;
	typedef void IP;
	typedef void ARR;
};

template <typename T>
class MotionableBPI : public TMotionable<T>
{
	using I = typename Motionable<T>::I;
	using MF = typename Motionable<T>::MF;
	H_BPI(MotionableBPI, I)
public:
	virtual float GetMotionTime() const override
	{
		return I::Execute_GetMotionTime(interface.GetObject());
	}
	virtual TMotionFrame<T> GetMotionFrame(float time) const override
	{
		return I::Execute_GetMotionFrame(interface.GetObject(), time);
	}
};

//*******************************************************************float************************************************************************************
UINTERFACE(MinimalAPI, Blueprintable)
class UMotionableF : public UInterface
{
	GENERATED_BODY()
};

class KISHILIB_API IMotionableF
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//Interface Abstract Methodes
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Motion")
	float GetMotionTime() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Motion")
	FMotionFrameF GetMotionFrame(float time) const;
};
//Proxy
UCLASS()
class KISHILIB_API UMotionableProxyF : public UObject, public IMotionableF
{
	GENERATED_BODY()
	using I = IMotionableF;
	using MF = FMotionFrameF;
	H_PROXY(UMotionableProxyF, I, TMotionable<float>)
public:
	virtual float GetMotionTime_Implementation() const override;
	virtual MF GetMotionFrame_Implementation(float time) const override;
};
//Array
UCLASS()
class KISHILIB_API UMotionableArrayF : public UObject, public IMotionableF
{
	GENERATED_BODY()
	using I = IMotionableF;
	using MF = FMotionFrameF;

public:
	UMotionableArrayF() = default;
	UMotionableArrayF(TArray<TScriptInterface<I>> _motions) : motions(_motions){};
	virtual float GetMotionTime_Implementation() const override;
	virtual MF GetMotionFrame_Implementation(float time) const override;

private:
	TArray<TScriptInterface<I>> motions;
};

template <>
struct Motionable<float>
{
	typedef IMotionableF I;
	typedef FMotionFrameF MF;
	typedef UMotionableProxyF IP;
	typedef UMotionableArrayF ARR;
};
//*******************************************************************FVector************************************************************************************
// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UMotionableFV : public UInterface
{
	GENERATED_BODY()
};

class KISHILIB_API IMotionableFV
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//Interface Abstract Methodes
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Motion")
	float GetMotionTime() const;
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Motion")
	FMotionFrameFV GetMotionFrame(float time) const;
};
//Proxy
UCLASS()
class KISHILIB_API UMotionableProxyFV : public UObject, public IMotionableFV
{
	GENERATED_BODY()
	using I = IMotionableFV;
	using MF = FMotionFrameFV;
	H_PROXY(UMotionableProxyFV, I, TMotionable<FVector>)
public:
	virtual float GetMotionTime_Implementation() const;
	virtual MF GetMotionFrame_Implementation(float time) const;
};
//Array
UCLASS()
class KISHILIB_API UMotionableArrayFV : public UObject, public IMotionableFV
{
	GENERATED_BODY()
	using I = IMotionableFV;
	using MF = FMotionFrameFV;

public:
	UMotionableArrayFV() = default;
	UMotionableArrayFV(TArray<TScriptInterface<I>> _motions) : motions(_motions){};
	virtual float GetMotionTime_Implementation() const override;
	virtual MF GetMotionFrame_Implementation(float time) const override;

private:
	TArray<TScriptInterface<I>> motions;
};
template <>
struct Motionable<FVector>
{
	typedef IMotionableFV I;
	typedef FMotionFrameFV MF;
	typedef UMotionableProxyFV IP;
	typedef UMotionableArrayFV ARR;
};

//**************************************************MACROS*************************************************
