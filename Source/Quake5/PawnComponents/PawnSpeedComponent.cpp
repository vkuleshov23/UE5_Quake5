// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnSpeedComponent.h"

// Sets default values for this component's properties
UPawnSpeedComponent::UPawnSpeedComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	MinSpeed = 200.0f;
	MaxSpeed = 2000.0f;
	WalkSpeed = 500.0f;
	RunSpeed = 1000.0f;
	MaxStamina = 100.f;
	Stamina = MaxStamina;
	TiredRidLimit = MaxStamina / 4;
	StaminaStep = 1.0f;
	bIsRun = false;
	bIsTired = false;
	ControllTikRate = 0.1f;
	JumpZVelocity = 700.f;
	AirControl = 0.35f;
	MinAnalogWalkSpeed = 20.0f;
	BrakingDecelerationWalking = 2000.f;
	BrakingDecelerationFalling = 1500.f;
}

UPawnSpeedComponent::~UPawnSpeedComponent()
{
}

// Called when the game starts
void UPawnSpeedComponent::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(TimerStaminaHandle, this, &UPawnSpeedComponent::StaminaControll, ControllTikRate, true);
}

void UPawnSpeedComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	GetWorld()->GetTimerManager().ClearTimer(TimerStaminaHandle);
}

// Called every frame
void UPawnSpeedComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

float UPawnSpeedComponent::GetSpeed()
{
	float Speed = GetSpeedBeforeAltering();
	Speed = Altering(Speed);
	Speed = fmax(Speed, MinSpeed);
	Speed = fmin(Speed, MaxSpeed);
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("Speed: %f"), Speed));
	return Speed;
}

void UPawnSpeedComponent::SetIsRun(bool _bIsRun)
{
	this->bIsRun = _bIsRun;
}

void UPawnSpeedComponent::AddSpeedAlter(USpeedAlteringEffectBase* SpeedAlter)
{
	ActiveSpeedAlters.Remove(SpeedAlter->GetEffectName());
	TWeakObjectPtr<USpeedAlteringEffectBase> SpeedAlterPtr = TWeakObjectPtr<USpeedAlteringEffectBase>(SpeedAlter);
	ActiveSpeedAlters.Add(SpeedAlter->GetEffectName(), SpeedAlterPtr);
	SpeedAlterPtr->Start();
}

float UPawnSpeedComponent::GetSpeedBeforeAltering()
{
	return IsRunningAvailable() ? RunSpeed : WalkSpeed;
}

void UPawnSpeedComponent::StaminaControll()
{
	if (IsRunningAvailable()) {
		if (Stamina > 0.0f) {
			Stamina = fmax(Stamina - StaminaStep, 0.0f);
		}
		else {
			bIsTired = true;
		}
	}
	else {
		if (Stamina >= TiredRidLimit) {
			bIsTired = false;
		}
		if (Stamina < MaxStamina) {
			Stamina = fmin(Stamina + StaminaStep, MaxStamina);
		}
	}
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT("%f"), Stamina));
}

bool UPawnSpeedComponent::IsRunningAvailable()
{
	return bIsRun && !bIsTired;
}


float UPawnSpeedComponent::Altering(float Speed)
{
	float AlterScale = 1.0f;
	for (TMap<FString, TWeakObjectPtr<USpeedAlteringEffectBase>>::TIterator Iter = ActiveSpeedAlters.CreateIterator(); Iter; ++Iter) {
		TWeakObjectPtr<USpeedAlteringEffectBase> Altering = Iter.Value();
		if (Altering.IsValid()) {
			if (Altering->IsOver()) {
				Iter.RemoveCurrent();
			}
			else {
				AlterScale += Altering->GetScale();
				GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Black, FString::Printf(TEXT("AlterScale: %f"), Altering->GetScale()));
			}
		}
	}
	return Speed * (AlterScale);
}