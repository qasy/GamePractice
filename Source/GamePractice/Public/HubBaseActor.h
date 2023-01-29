// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.h"
#include "HubBaseActor.generated.h"

UCLASS()
class GAMEPRACTICE_API AHubBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHubBaseActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseActor> SpawnedClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	void SpawnChild();

};
