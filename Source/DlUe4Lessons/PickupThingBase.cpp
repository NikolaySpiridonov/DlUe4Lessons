// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupThingBase.h"

// Sets default values
APickupThingBase::APickupThingBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Thing body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereisualAsset(
		TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereisualAsset.Succeeded())
		StaticMesh->SetStaticMesh(SphereisualAsset.Object);
	RootComponent = StaticMesh;
	StaticMesh->SetGenerateOverlapEvents(true);
	//StaticMesh->OnComponentHit.AddDynamic(this, &APickupThingBase::OnHit);
}

// Called when the game starts or when spawned
void APickupThingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickupThingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SecondsToDestroy -= DeltaTime;
	if (SecondsToDestroy <= 0)
		Destroy();

}


