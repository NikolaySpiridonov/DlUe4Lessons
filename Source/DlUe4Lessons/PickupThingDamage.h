// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickupThingBase.h"
#include "PickupThingDamage.generated.h"

/**
 * 
 */
UCLASS()
class DLUE4LESSONS_API APickupThingDamage : public APickupThingBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 100))
	int DamageValue = 50;

public:
	virtual void OnPickup(int& PlayerHealth, float& ConstHealthTimer) override;
	
	APickupThingDamage();
};
