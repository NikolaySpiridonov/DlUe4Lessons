// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratorOfPickupThings.h"
#include "Math/UnrealMathUtility.h"
#include "Components/SceneComponent.h"
#include "PickupThingTimerStop.h"


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
		FMath::RandRange(-MaxSpawnBoundByAxis, MaxSpawnBoundByAxis), 
		FMath::RandRange(-MaxSpawnBoundByAxis, MaxSpawnBoundByAxis), 
		0);

	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector PlayerLocation; 
	if(PlayerPawn)
		PlayerLocation = PlayerPawn->GetActorLocation();
	if (FVector::Distance(PlayerLocation, NewActorLocation) < MinDistanceToPlayer)
		return;

	APickupThingBase *NewActor = nullptr;
	auto PickupThingsNum = ArrayPickupThingsTypes.Num();
	auto RandomIndex = FMath::RandRange(0, PickupThingsNum - 1);
	if(PickupThingsNum > 0)
		NewActor = World->SpawnActor<APickupThingBase>(
			ArrayPickupThingsTypes[RandomIndex],
			NewActorLocation, 
			FRotator(0.0f, 0.0f, 0.0f), 
			ActorSpawnParameters);
	
	if (NewActor)
	{
		NewActor->SetSecondsToDestroy(PickupThingLifeTime);
		ArraySpawnedThings.Add(NewActor);

		auto PickupThingTimerStop = Cast<APickupThingTimerStop>(NewActor);
		if (PickupThingTimerStop)
			PickupThingTimerStop->SetTimerStopDuration(TimerStopDuration);
	}

}

// Called every frame
void AGeneratorOfPickupThings::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PickupThingsSpawningTick(DeltaTime);

}

