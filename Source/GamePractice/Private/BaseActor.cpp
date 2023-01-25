// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include  "Engine/Engine.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));
	SetRootComponent(StaticMeshComponent);
	DeltaPosition = FVector(0.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ABaseActor::Move()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	float Time = World->GetTimeSeconds();
	FVector Location = GetActorLocation();
	
	Location += DeltaPosition;
	UE_LOG(LogTemp, Error, TEXT("%s"), *Location.ToString());

	//AngleRotation *= Time;
//	Rotator.Add(AngleRotation.Pitch, AngleRotation.Yaw, AngleRotation.Roll);
//	SetActorLocation(Location);
	SetActorLocation(Location);
}

