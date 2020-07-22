// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupThingTimerStop.h"

APickupThingTimerStop::APickupThingTimerStop()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("Material'/Game/MaterialYellow.MaterialYellow'"));

	if (MaterialFinder.Succeeded())
		StaticMesh->SetMaterial(0, MaterialFinder.Object);
}

void APickupThingTimerStop::SetTimerStopDuration(const float& _TimerStopDuration)
{
	TimerStopDuration = _TimerStopDuration;
}

void APickupThingTimerStop::OnPickup(int& PlayerHealth, float& ConstHealthTimer)
{
	ConstHealthTimer += TimerStopDuration;

	ConstHealthTimer = FMath::Clamp(ConstHealthTimer + TimerStopDuration, 0.0f, 100.0f);
	Destroy();
}
