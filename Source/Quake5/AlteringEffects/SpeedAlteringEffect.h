// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AlteringEffect.h"
#include "UObject/Interface.h"
#include "SpeedAlteringEffect.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpeedAlteringEffect : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class QUAKE5_API ISpeedAlteringEffect : public IAlteringEffect
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:	
	UFUNCTION()
	virtual void SetScale(float scale);
	UFUNCTION()
	virtual float GetScale();
protected:
	float Scale = 0.0f;
};
