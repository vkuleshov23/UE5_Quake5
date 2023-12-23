// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpeedAlteringEffect.h"
#include "SpeedAlteringEffectBase.generated.h"

/**
 * 
 */
UCLASS()
class QUAKE5_API USpeedAlteringEffectBase : public UObject, public ISpeedAlteringEffect
{
	GENERATED_BODY()
public:
	USpeedAlteringEffectBase(): ISpeedAlteringEffect(){}
	virtual ~USpeedAlteringEffectBase() {};
};
