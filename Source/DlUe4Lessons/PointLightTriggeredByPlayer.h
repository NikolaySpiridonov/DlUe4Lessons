// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PointLightTriggeredByPlayer.generated.h"


UCLASS()
class DLUE4LESSONS_API APointLightTriggeredByPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointLightTriggeredByPlayer();

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* LightMesh = nullptr;

	UPROPERTY(EditAnywhere)
	class UTextRenderComponent* TextLabel = nullptr;

	UPROPERTY(EditAnywhere)
	class UPointLightComponent* Light = nullptr;

	UPROPERTY(EditAnywhere)
	int LightTriggerDistance = 250;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
