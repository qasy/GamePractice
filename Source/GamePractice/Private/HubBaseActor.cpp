// Fill out your copyright notice in the Description page of Project Settings.
#include "HubBaseActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogHubBaseActor, All, All)

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

	// SpawnChild();
	// SpawnChildDeffered();
	// SpawnChildOnTimer();
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AHubBaseActor::SpawnChildOnTimer, SpawnTimerRate, true);
	
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
		for (int32 i = 0; i < MaxSpawnedActorCounter; ++i)
		{
			FVector Location = GetActorLocation();
			Location.X += i * 200.f;
			ABaseActor* SpawnedActor = World->SpawnActor<ABaseActor>(SpawnedClass, FTransform(FRotator::ZeroRotator, Location));
		}
	}
}

void AHubBaseActor::SpawnChildDeffered()
{
	UWorld* World = GetWorld();
	if (World)
	{
		for (int32 i = 0; i < MaxSpawnedActorCounter; ++i)
		{
			FVector Location = GetActorLocation();
			Location.X += i * 200.f;
			Location.Z += 200.0f;
			ABaseActor* SpawnedActor = World->SpawnActorDeferred<ABaseActor>(SpawnedClass, FTransform(FRotator::ZeroRotator, Location));
			
			if (SpawnedActor)
			{
				FMovementData TmpMoveData;
				TmpMoveData.MovementType = FMath::RandBool() ? EMovementType::Static : EMovementType::Sin;
				TmpMoveData.MovementType = (TmpMoveData.MovementType == EMovementType::Static) ? EMovementType::Static : EMovementType::Rotate;
				SpawnedActor->SetMovementData(TmpMoveData);
				SpawnedActor->SetColor(FLinearColor::MakeRandomColor());
				SpawnedActor->FinishSpawning(FTransform(FRotator::ZeroRotator, Location));

			}
		}
	}
}

void AHubBaseActor::SpawnChildOnTimer()
{
	UWorld* World = GetWorld();
	if (World)
	{
		if (SpawnedActorCounter++ < MaxSpawnedActorCounter)
		{
			FTransform HubTransform = GetActorTransform();
			FVector HubLocation = HubTransform.GetLocation();
			FVector SpawnLocation = HubLocation + FVector(200.0f * SpawnedActorCounter, 0.0f, 0.0f);
			FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, SpawnLocation);
			ABaseActor* SpawnedActor = World->SpawnActorDeferred<ABaseActor>(SpawnedClass, SpawnTransform);
			if (SpawnedActor)
			{
				SpawnedActor->FinishSpawning(SpawnTransform);
			}
		}
		else
		{
			GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
			UE_LOG(LogHubBaseActor, Warning, TEXT("%s finished spawning"), *GetName());
		}
	}
}
