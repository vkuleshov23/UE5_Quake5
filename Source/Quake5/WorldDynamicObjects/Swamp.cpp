// Fill out your copyright notice in the Description page of Project Settings.

#include "../HeroCharacter.h"
#include "../AlteringEffects/SpeedSlowdownEffect.h"
#include "../PawnComponents/PawnSpeedComponent.h"
#include "Swamp.h"

// Sets default values
ASwamp::ASwamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SwampMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwampMesh"));
	SetRootComponent(SwampMesh);
	SwampMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SwampMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	SwampSlowdownScale = 20.0f;
	SwampSlowdownDurationInSec = 2.5f;
}

// Called when the game starts or when spawned
void ASwamp::BeginPlay()
{
	Super::BeginPlay();

	SwampSlowdownUpdateForInsideInSec = SwampSlowdownDurationInSec * 0.8;

	SwampMesh->OnComponentBeginOverlap.AddDynamic(this, &ASwamp::OnBeginOverlap);
	SwampMesh->OnComponentEndOverlap.AddDynamic(this, &ASwamp::OnEndOverlap);
	GetWorldTimerManager().SetTimer(TimerSwampSlowdownUpdateHandle, this, &ASwamp::SwampSlowdownUpdateControll, SwampSlowdownUpdateForInsideInSec, true);

	SwampSlowadown = NewObject<USpeedSlowdownEffect>();
	SwampSlowadown->SetEffectName("Swamp Slowdown");
	SwampSlowadown->SetScale(SwampSlowdownScale);
	SwampSlowadown->SetTimeDurationInSec(SwampSlowdownDurationInSec);
	
}

void ASwamp::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(TimerSwampSlowdownUpdateHandle);
}

void ASwamp::SwampSlowdownUpdateControll()
{
	for (TSet<TWeakObjectPtr<AHeroCharacter>>::TIterator Iter = PawnInSwamp.CreateIterator(); Iter; ++Iter) {
		TWeakObjectPtr<AHeroCharacter> Character = *Iter;
		if (Character.IsValid()) {
			Character->SpeedComponent->AddSpeedAlter(SwampSlowadown);
		}
	}
}

// Called every frame
void ASwamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASwamp::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AHeroCharacter* Character = Cast<AHeroCharacter>(OtherActor);
	if (Character) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("It is a Character"));
		PawnInSwamp.Add(Character);
		Character->SpeedComponent->AddSpeedAlter(SwampSlowadown);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("It is NOT a Character"));
	}
}

void ASwamp::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AHeroCharacter* Character = Cast<AHeroCharacter>(OtherActor);
	if (Character) {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, TEXT("End It is a Character"));
		PawnInSwamp.Remove(Character);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("End It is NOT a Character"));
	}
}

