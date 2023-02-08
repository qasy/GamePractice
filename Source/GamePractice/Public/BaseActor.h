// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

// Call, when timer has stopped
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLifeTimerFinished, AActor*);

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Static,
	Sin,
	Rotate
};

USTRUCT(BlueprintType)
struct FMovementData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FTransform InitialTransform = FTransform(FRotator::ZeroRotator, FVector::ZeroVector);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementType MovementType = EMovementType::Static;
};


UCLASS()
class GAMEPRACTICE_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMovementData(const FMovementData& Data);
	void SetColor(const FLinearColor& Color);
	void SetMaxLifeCounter(int32 newValue);

	FOnLifeTimerFinished OnLifeTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FMovementData MovementData;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	//FLinearColor Color = FLinearColor::Black;


private:
	FTimerHandle LifeTimerHandle;
	float LifeTimerRate = 1.0f;
	int32 LifeTimerCounter = 0;
	int32 MaxLifeTimerCounter = 5;

	FTimerHandle ColorTimerHandle; // Timer descriptor
	float ColorTimerRate = 1.0f;
	int32 MaxColorTimerCounter = 10;
	int32 ColorTimerCounter = 0;

	void Move();

	// Function called by the timer
	void OnColorTimerFired();
	void OnLifeTimerFired();
	
};
