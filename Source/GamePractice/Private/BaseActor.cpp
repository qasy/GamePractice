// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));
	SetRootComponent(StaticMeshComponent);

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
	
	UWorld* World = GetWorld();
	if(!World)
	{
		return;
	}



}

void ABaseActor::Move()
{
	float Time = World->GetTimeSeconds();
	FRotator Rotator = GetActorRotation();

	AngleRotation *= Time;
	Rotator.Add(AngleRotation.Pitch, AngleRotation.Yaw, AngleRotation.Roll);
	SetActorRotation(Rotator);
}

