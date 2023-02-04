// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseActor.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseActor, All, All)

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
	// GetWorldTimerManager().SetTimer(ColorTimerHandle, this, &ABaseActor::OnColorTimerFired, ColorTimerRate, true);
	GetWorldTimerManager().SetTimer(LifeTimerHandle, this, &ABaseActor::OnLifeTimerFired, LifeTimerRate, true);
	MovementData.InitialTransform = GetActorTransform();
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
	if (World)
	{
		float Time = World->GetTimeSeconds();

		// Want to set harmonical movement
		if (MovementData.MovementType == EMovementType::Sin)
		{
			FVector InitialLocation = MovementData.InitialTransform.GetLocation();
			FVector CurrentLocation = InitialLocation + MovementData.Amplitude * FMath::Sin(MovementData.Frequency * Time);
			SetActorLocation(CurrentLocation);
		}
		else if (MovementData.MovementType == EMovementType::Rotate)
		{
			FRotator InitialRotation = MovementData.InitialTransform.Rotator();
			FRotator CurrentRotation = InitialRotation + FRotator(0.0f, MovementData.Amplitude*FMath::Sin(MovementData.Frequency * Time), 0.0f);
			SetActorRotation(CurrentRotation);
		}

	
		// UE_LOG(LogBaseActor, Error, TEXT("%s"), *CurrentLocation.ToString());		
	}	
	//UE_LOG(LogBaseActor, Warning, TEXT("Move(): Name: %s, %0.1f"), *GetName(), MovementData.Frequency);
}

void ABaseActor::SetColor(const FLinearColor& Color)
{
	UWorld* World = GetWorld();
	if (World)
	{
		UMaterialInstanceDynamic* DynMaterial = StaticMesh->CreateAndSetMaterialInstanceDynamic(0);
		if (DynMaterial)
		{
			// Set value to Color parameter, which one we named from blueprint
			DynMaterial->SetVectorParameterValue("Color", Color);
			UE_LOG(LogBaseActor, Error, TEXT("New color: %s "), *Color.ToString());
		}
	}	
}

void ABaseActor::SetMovementData(const FMovementData& MData)
{
	MovementData = MData;
}

void ABaseActor::OnColorTimerFired()
{	
	// Function called by the timer
	if (ColorTimerCounter++ < MaxColorTimerCounter)
	{
		SetColor(FLinearColor::MakeRandomColor());		
		UE_LOG(LogBaseActor, Warning, TEXT("%s timer counter %d/%d."), *GetName(), ColorTimerCounter, MaxColorTimerCounter);
	}
	else
	{
		GetWorldTimerManager().ClearTimer(ColorTimerHandle);
		UE_LOG(LogBaseActor, Warning, TEXT("%s clear timer."), *GetName());
	}
	
}

void ABaseActor::OnLifeTimerFired()
{
	if (LifeTimerCounter++ < MaxLifeTimerCounter)
	{
		UE_LOG(LogBaseActor, Warning, TEXT("%s have a %d seconds before destroy"), *GetName(), LifeTimerCounter);	
	}
	else
	{
		GetWorldTimerManager().ClearTimer(LifeTimerHandle);
		if (OnLifeTimerFinished.IsBound())
		{
			OnLifeTimerFinished.Broadcast(this);
		}
		Destroy();
		UE_LOG(LogBaseActor, Error, TEXT("%s was destroyed!"), *GetName());
	}
}

void ABaseActor::SetMaxLifeCounter(int32 newValue)
{
	MaxLifeTimerCounter = (newValue > 0) ? newValue : MaxLifeTimerCounter;
}