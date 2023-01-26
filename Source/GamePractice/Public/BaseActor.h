// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UCLASS()
class GAMEPRACTICE_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector InitialLocation;
	
	UPROPERTY(EditAnywhere, Category = "Movement")
	FVector DeltaPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 10.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Move();
	void ChangeColor();
};
