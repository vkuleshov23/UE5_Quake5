// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedAlteringEffect.h"

// Add default functionality here for any ISpeedAlteringEffect functions that are not pure virtual.

void ISpeedAlteringEffect::SetScale(float scale)
{
	if (scale >= 0.0f) {
		this->Scale = scale;
	}
}

float ISpeedAlteringEffect::GetScale()
{
	return Scale;
}