// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedSlowdownEffect.h"

float USpeedSlowdownEffect::GetScale()
{
	return -(this->ISpeedAlteringEffect::GetScale());
}
