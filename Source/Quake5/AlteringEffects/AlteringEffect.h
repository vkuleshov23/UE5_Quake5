// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AlteringEffect.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAlteringEffect : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class QUAKE5_API IAlteringEffect
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual int64 GetTimeInSec();
	UFUNCTION()
	virtual FString GetEffectName();
	UFUNCTION()
	virtual void SetEffectName(FString name);
	UFUNCTION()
	virtual void SetTimeDurationInSec(float timeInSec);
	UFUNCTION()
	virtual void Start();
	UFUNCTION()
	virtual bool IsOver();
	UFUNCTION()
	virtual void AddTimeInSec(float timeInSec);
	UFUNCTION()
	virtual void SubTimeInSec(float timeInSec);

protected:
	int64 ToTicks(float timeInSec);
	float ToSec(int64 timeInTicks);

protected:
	int64 TimeDurationInTicks = 0;
	FDateTime StartTime;
	FString Name;
};
