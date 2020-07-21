// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorOfPickupThings.h"
#include "PickupThingHealthUp.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"


// Sets default values
AGeneratorOfPickupThings::AGeneratorOfPickupThings()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
}

// Called when the game starts or when spawned
void AGeneratorOfPickupThings::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGeneratorOfPickupThings::PickupThingsSpawningTick(float DeltaTime)
{
	ArraySpawnedThings.RemoveAll
	(
		[](APickupThingBase* val)
		{
			return val->IsPendingKill();
		}
	);

	if (ArraySpawnedThings.Num() < MaxPickupThings)
		SpawnPickupThing();
}

void AGeneratorOfPickupThings::SpawnPickupThing()
{
	auto World = GetWorld();
	FActorSpawnParameters ActorSpawnParameters;
	//if can`t place at this frame will try in next
	ActorSpawnParameters.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	FVector NewActorLocation;
	NewActorLocation = GetActorLocation() + FVector(
		FMath::RandRange(0, MaxSpawnBoundByAxis), FMath::RandRange(0, MaxSpawnBoundByAxis), 0);

	auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	if (FVector::Distance(PlayerLocation, NewActorLocation) < MinDistanceToPlayer)
		return;

	auto NewActor = World->SpawnActor<APickupThingHealthUp>(
		NewActorLocation, FRotator(0.0f, 0.0f, 0.0f), ActorSpawnParameters);
	
	if(NewActor)
		ArraySpawnedThings.Add(NewActor);

}

// Called every frame
void AGeneratorOfPickupThings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PickupThingsSpawningTick(DeltaTime);

}

