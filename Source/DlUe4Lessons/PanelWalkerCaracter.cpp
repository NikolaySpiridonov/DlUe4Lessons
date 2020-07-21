// Fill out your copyright notice in the Description page of Project Settings.


#include "PanelWalkerCaracter.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
APanelWalkerCaracter::APanelWalkerCaracter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent->OnComponentHit.AddDynamic(this, &APanelWalkerCaracter::OnHit);
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

	SecondCounter += DeltaTime;
	if (SecondCounter >= 1)
	{
		SecondCounter = 0;
		Health = FMath::Clamp(Health - HealthDecreasingStepPerSec, 0, 100);
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
	bool t = true;

}

