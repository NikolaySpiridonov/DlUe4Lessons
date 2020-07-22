// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupThingHealthUp.h"
#include "Math/UnrealMathUtility.h"
#include "Materials/Material.h"

void APickupThingHealthUp::OnPickup(int& PlayerHealth, float& ConstHealthTimer)
{
	PlayerHealth = FMath::Clamp(PlayerHealth + HealtUpValue, 0, 100);
	Destroy();
}

APickupThingHealthUp::APickupThingHealthUp()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("Material'/Game/MaterialGreen.MaterialGreen'"));

	if(MaterialFinder.Succeeded())
		StaticMesh->SetMaterial(0, MaterialFinder.Object);
}
