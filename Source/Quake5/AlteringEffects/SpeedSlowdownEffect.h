// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SpeedAlteringEffectBase.h"
#include "SpeedSlowdownEffect.generated.h"

/**
 * 
 */
UCLASS()
class QUAKE5_API USpeedSlowdownEffect : public USpeedAlteringEffectBase
{
	GENERATED_BODY()
public:
	USpeedSlowdownEffect() {}
	virtual ~USpeedSlowdownEffect() {}

	float GetScale() override;

};
