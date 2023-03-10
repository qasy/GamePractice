// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.h"
#include "HubBaseActor.generated.h"

USTRUCT(BlueprintType)
struct FSpawnedPayloads
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseActor> SpawnedClass;

	UPROPERTY(EditAnywhere)
	FLinearColor BeginColor;

	UPROPERTY(EditAnywhere)
	FMovementData MovementData;
};

UCLASS()
class GAMEPRACTICE_API AHubBaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHubBaseActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseActor> SpawnedClass;

	UPROPERTY(EditAnywhere)
	int32 MaxSpawnedActorCounter = 10;

	UPROPERTY(EditAnywhere)
	TArray<FSpawnedPayloads> SpawnedPayloads;

private: 

	FTimerHandle SpawnTimerHandle;
	float SpawnTimerRate = 1.0f;
	int32 SpawnedActorCounter = 0;


	void SpawnChild();
	void SpawnChildDeffered();
	void SpawnChildOnTimer();
	void SpawnFromArray();
	void SpawnReplacement(AActor* Actor);

};
