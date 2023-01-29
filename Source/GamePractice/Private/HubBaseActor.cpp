// Fill out your copyright notice in the Description page of Project Settings.
#include "HubBaseActor.h"

// Sets default values
AHubBaseActor::AHubBaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHubBaseActor::BeginPlay()
{
	Super::BeginPlay();
	SpawnChild();
	
}

// Called every frame
void AHubBaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHubBaseActor::SpawnChild()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FTransform Transform = GetActorTransform();
		ABaseActor* SpawnedActor = World->SpawnActor<ABaseActor>(SpawnedClass, Transform);
	}

}

