// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PickupThingBase.h"

#include "GeneratorOfPickupThings.generated.h"

UCLASS()
class DLUE4LESSONS_API AGeneratorOfPickupThings : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratorOfPickupThings();

	UPROPERTY(EditAnywhere)
	class USceneComponent* SceneComponent = nullptr;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 10))
	int MaxPickupThings = 2;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 100))
	int MinDistanceToPlayer = 200;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 60))
	int PickupThingLifeTime = 5;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 1, ClampMax = 60))
	int TimerStopDuration = 5;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 100))
	int MaxSpawnBoundByAxis = 2000;

	UPROPERTY(VisibleAnywhere)
	TArray<APickupThingBase*> ArraySpawnedThings;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<class APickupThingBase>> ArrayPickupThingsTypes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PickupThingsSpawningTick(float DeltaTime);

	void SpawnPickupThing();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
