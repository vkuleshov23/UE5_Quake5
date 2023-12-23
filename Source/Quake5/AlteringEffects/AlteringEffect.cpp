// Fill out your copyright notice in the Description page of Project Settings.


#include "AlteringEffect.h"

// Add default functionality here for any IAlteringEffect functions that are not pure virtual.

float IAlteringEffect::ToSec(int64 timeInTicks)
{
	return (float)(timeInTicks / ETimespan::TicksPerSecond);
}

int64 IAlteringEffect::ToTicks(float timeInSec)
{
	return (int64)(timeInSec * ETimespan::TicksPerSecond);
}

int64 IAlteringEffect::GetTimeInSec()
{
	return ToSec(TimeDurationInTicks);
}

FString IAlteringEffect::GetEffectName()
{
	return Name;
}

void IAlteringEffect::SetEffectName(FString name)
{
	this->Name = name;
}

void IAlteringEffect::SetTimeDurationInSec(float timeInSec)
{
	if (timeInSec >= 0) {
		this->TimeDurationInTicks = ToTicks(timeInSec);
	}
}

void IAlteringEffect::Start()
{
	StartTime = FDateTime::Now();
}

bool IAlteringEffect::IsOver()
{
	return (StartTime.GetTicks() + TimeDurationInTicks) < (FDateTime::Now().GetTicks());
}

void IAlteringEffect::AddTimeInSec(float timeInSec)
{
	TimeDurationInTicks += ToTicks(timeInSec);
}

void IAlteringEffect::SubTimeInSec(float timeInSec)
{
	TimeDurationInTicks -= ToTicks(timeInSec);
}
