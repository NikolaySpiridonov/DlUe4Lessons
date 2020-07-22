// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupThingBase.generated.h"

//don`t forget to add childs of this class to collection of generator to Spawn
UCLASS(abstract)
class DLUE4LESSONS_API APickupThingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupThingBase();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	float SecondsToDestroy = 5;

	UPROPERTY(VisibleAnywhere)
	class UMaterial *Material;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnPickup(int& PlayerHealth, float& ConstHealthTimer) PURE_VIRTUAL(APickupThingBase::OnPickup);

	UFUNCTION()
	void SetSecondsToDestroy(const float &_SecondsToDestroy);

};
