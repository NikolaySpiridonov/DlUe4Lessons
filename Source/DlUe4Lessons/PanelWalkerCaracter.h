// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PanelWalkerCaracter.generated.h"

UCLASS()
class DLUE4LESSONS_API APanelWalkerCaracter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APanelWalkerCaracter();

	UPROPERTY(VisibleAnywhere)
	int Health = 100;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 100))
	int HealthDecreasingStepPerSec = 5;

	float SecondCounter = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void OnHit
	(
		UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, 
		const FHitResult& Hit
	);

};
