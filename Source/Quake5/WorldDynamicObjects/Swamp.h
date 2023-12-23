// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Swamp.generated.h"

class AHeroCharacter;
class USpeedSlowdownEffect;
class UPawnSpeedComponent;

UCLASS()
class QUAKE5_API ASwamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwamp();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
	UStaticMeshComponent* SwampMesh;

	UPROPERTY()
	USpeedSlowdownEffect* SwampSlowadown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SwampSlowdownDurationInSec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SwampSlowdownScale;

	UPROPERTY()
	float SwampSlowdownUpdateForInsideInSec;

	UPROPERTY()
	FTimerHandle TimerSwampSlowdownUpdateHandle;

	TSet<TWeakObjectPtr<AHeroCharacter>> PawnInSwamp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the game end or when destroyed
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void SwampSlowdownUpdateControll();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
