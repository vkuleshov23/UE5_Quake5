// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpeedAlteringEffectBase.h"
#include "SpeedAmplifyEffect.generated.h"

/**
 * 
 */
UCLASS()
class QUAKE5_API USpeedAmplifyEffect : public USpeedAlteringEffectBase
{
	GENERATED_BODY()
public:
	USpeedAmplifyEffect() {}
	virtual ~USpeedAmplifyEffect() {}
};
