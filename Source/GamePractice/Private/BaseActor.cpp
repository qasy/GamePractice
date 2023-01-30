// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include  "Engine/Engine.h"
#include  "Materials/MaterialInstanceDynamic.h"

// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh Component"));
	SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();
	SetColor(FLinearColor::MakeRandomColor());
}

// Called every frame
void ABaseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
	SetColor(FLinearColor::MakeRandomColor());
}

void ABaseActor::Move()
{
	UWorld* World = GetWorld();
	if (World)
	{
		float Time = World->GetTimeSeconds();
		FVector CurrentLocation = GetActorLocation();

		// Want to set harmonical movement
		CurrentLocation = InitialLocation + DeltaPosition * FMath::Sin(Frequency * Time);

		SetActorLocation(CurrentLocation);
		// UE_LOG(LogTemp, Error, TEXT("%s"), *CurrentLocation.ToString());		
	}	
}

void ABaseActor::SetColor(const FLinearColor& Color)
{
	UWorld* World = GetWorld();
	if (World)
	{
		ColorTimeCurrent = World->GetTimeSeconds();
		float DeltaTime = ColorTimeCurrent - ColorTimeStart;
		if (StaticMesh && (DeltaTime > ColorChangeRate || FMath::IsNearlyZero(DeltaTime)) )
		{
			// UE_LOG(LogTemp, Warning, TEXT("%d"), FMath::IsNearlyZero(DeltaTime));
			UMaterialInstanceDynamic* DynMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
			if (DynMaterial)
			{
				// @todo: not working color change
				DynMaterial->SetVectorParameterValue("Color", Color);
				
				UE_LOG(LogTemp, Error, TEXT("%s delta time sec: %0.1f"), *Color.ToString(), DeltaTime);
				ColorTimeStart = ColorTimeCurrent;
			}
		}

	}

	
}
