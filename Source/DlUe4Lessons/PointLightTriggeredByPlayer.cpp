// Fill out your copyright notice in the Description page of Project Settings.


#include "PointLightTriggeredByPlayer.h"

#include "Components/PointLightComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APointLightTriggeredByPlayer::APointLightTriggeredByPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Light Body"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereisualAsset(
		TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (SphereisualAsset.Succeeded())
		LightMesh->SetStaticMesh(SphereisualAsset.Object);
	RootComponent = LightMesh;

	TextLabel = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text Label"));
	TextLabel->SetupAttachment(RootComponent);
	TextLabel->SetText(TEXT("Come to me!"));
	

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Triggered Light Component"));
	Light->SetupAttachment(RootComponent);
	Light->SetLightColor(FLinearColor::Red);
	Light->SetIntensity(100000);

}

// Called when the game starts or when spawned
void APointLightTriggeredByPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector PlayerLocation;
	if (PlayerPawn)
		PlayerLocation = PlayerPawn->GetActorLocation();
	auto ActorLocation = GetActorLocation();
	TextLabel->SetRelativeRotation(UKismetMathLibrary::FindLookAtRotation(ActorLocation, PlayerLocation));
	TextLabel->AddLocalOffset(FVector(-10.0f, TextLabel->GetTextWorldSize().Y / 2, 50.0f));
	
}

// Called every frame
void APointLightTriggeredByPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Not the best way to do that in Tick(), cause there are trigger system, but let it be
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector PlayerLocation;
	if (PlayerPawn)
		PlayerLocation = PlayerPawn->GetActorLocation();
	auto ActorLocation = GetActorLocation();
	
	Light->SetVisibility(
		FVector::Distance(PlayerLocation, ActorLocation) < LightTriggerDistance);
}

