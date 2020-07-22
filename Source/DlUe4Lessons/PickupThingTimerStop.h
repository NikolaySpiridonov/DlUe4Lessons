// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupThingBase.h"
#include "PickupThingTimerStop.generated.h"

/**
 * 
 */
UCLASS()
class DLUE4LESSONS_API APickupThingTimerStop : public APickupThingBase
{
	GENERATED_BODY()

public:

	UPROPERTY()
	float TimerStopDuration = 5;

public:

	virtual void OnPickup(int& PlayerHealth, float& ConstHealthTimer) override;

	APickupThingTimerStop();

	void SetTimerStopDuration(const float& _TimerStopDuration);
	
};
