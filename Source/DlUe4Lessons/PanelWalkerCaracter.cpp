// Fill out your copyright notice in the Description page of Project Settings.


#include "PanelWalkerCaracter.h"
#include "Math/UnrealMathUtility.h"
#include "Components/CapsuleComponent.h"
#include "PickupThingBase.h"

// Sets default values
APanelWalkerCaracter::APanelWalkerCaracter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	auto comp = GetCapsuleComponent();
	comp->OnComponentHit.AddDynamic(this, &APanelWalkerCaracter::OnHit);
}

// Called when the game starts or when spawned
void APanelWalkerCaracter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = 100;
}

// Called every frame
void APanelWalkerCaracter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TimerStopSecsLeft > 0)
	{
		TimerStopSecsLeft = FMath::Max(TimerStopSecsLeft - DeltaTime, 0.0f);
		GEngine->AddOnScreenDebugMessage(1, 0.0f, FColor::Yellow, TEXT("Timer stopped"));
	}
	else
	{
		SecondCounter += DeltaTime;
		if (SecondCounter >= 1)
		{
			SecondCounter = 0;
			Health = FMath::Clamp(Health - HealthDecreasingStepPerSec, 0, 100);
		}
	}

	if (Health == 0)
	{
		GEngine->AddOnScreenDebugMessage(0, 10.0f, FColor::Red, TEXT("YOU`RE DEAD"));
		Destroy();
		return;
	}

	FString HealthString = FString::Printf(TEXT("Health: %d"), Health);
	GEngine->AddOnScreenDebugMessage(0, 0.0f, FColor::Green, HealthString);

}

// Called to bind functionality to input
void APanelWalkerCaracter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APanelWalkerCaracter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APanelWalkerCaracter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APanelWalkerCaracter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APanelWalkerCaracter::AddControllerPitchInput);
}

void APanelWalkerCaracter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APanelWalkerCaracter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void APanelWalkerCaracter::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto PickupThing = Cast<APickupThingBase>(OtherActor);
	if (PickupThing)
		PickupThing->OnPickup(Health, TimerStopSecsLeft);

}

