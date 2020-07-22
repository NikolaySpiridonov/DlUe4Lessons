// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupThingDamage.h"

void APickupThingDamage::OnPickup(int& PlayerHealth, float& ConstHealthTimer)
{
	PlayerHealth = FMath::Clamp(PlayerHealth - DamageValue, 0, 100);
	Destroy();
}

APickupThingDamage::APickupThingDamage()
{
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialFinder(TEXT("Material'/Game/MaterialRed.MaterialRed'"));
	if (MaterialFinder.Succeeded())
		StaticMesh->SetMaterial(0, MaterialFinder.Object);
}
