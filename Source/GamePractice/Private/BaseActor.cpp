// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include  "Engine/Engine.h"
#include  "Materials/MaterialInstanceDynamic.h"

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
	InitialLocation = GetActorLocation();
	
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	ChangeColor();
}

void ABaseActor::Move()
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	float Time = World->GetTimeSeconds();
	FVector CurrentLocation = GetActorLocation();

	// Want to set harmonical movement
	CurrentLocation = InitialLocation + DeltaPosition * FMath::Sin(Frequency * Time);
	
	SetActorLocation(CurrentLocation);
	// UE_LOG(LogTemp, Error, TEXT("%s"), *CurrentLocation.ToString());
}

void ABaseActor::ChangeColor()
{
	if (StaticMeshComponent)
	{
		UMaterialInstanceDynamic* DynamicMaterial = StaticMeshComponent->CreateAndSetMaterialInstanceDynamic(0);
		if(DynamicMaterial)
		{
			// @todo: not working color change
			FLinearColor Color = FLinearColor::MakeRandomColor();
			DynamicMaterial->SetVectorParameterValue("Color", Color);
			UE_LOG(LogTemp, Error, TEXT("%s"), *Color.ToString());
		}		
	}

}
