// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupThingHealthUp.h"
#include "Math/UnrealMathUtility.h"

void APickupThingHealthUp::OnPickup(int& PlayerHealth, float& ConstHealthTimer)
{
	PlayerHealth = FMath::Clamp(PlayerHealth + HealtUpValue, 0, 100);

}
