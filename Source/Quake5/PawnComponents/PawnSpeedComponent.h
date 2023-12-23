// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../AlteringEffects/SpeedAlteringEffectBase.h"
#include "PawnSpeedComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class QUAKE5_API UPawnSpeedComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPawnSpeedComponent();
	virtual ~UPawnSpeedComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Called when the game end or when destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void StaminaControll();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	float GetSpeed();

	UFUNCTION()
	void SetIsRun(bool _bIsRun);

	UFUNCTION()
	void AddSpeedAlter(USpeedAlteringEffectBase* SpeedAlter);

	UFUNCTION()
	float GetSpeedBeforeAltering();

	UFUNCTION()
	bool IsRunningAvailable();


	UFUNCTION()
	float Altering(float Speed);

protected:
	TMap<FString, TWeakObjectPtr<USpeedAlteringEffectBase>> ActiveSpeedAlters;
	UPROPERTY()
	bool bIsRun;
	UPROPERTY()
	bool bIsTired;
	UPROPERTY()
	float Stamina;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float StaminaStep;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TiredRidLimit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ControllTikRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpZVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AirControl;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinAnalogWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BrakingDecelerationWalking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BrakingDecelerationFalling;

	UPROPERTY()
	FTimerHandle TimerStaminaHandle;
		
};
