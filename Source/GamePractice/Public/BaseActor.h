// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

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
	EMovementType MovementType = EMovementType::Rotate;
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

	void SetColor(const FLinearColor& Color);
	void SetMovementData(const FMovementData& MData);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Movement")
	FMovementData MovementData;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	//FLinearColor Color = FLinearColor::Black;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Design")
	float ColorChangeRate = 5.0f;

	float ColorTimeStart = 0.0f;
	float ColorTimeCurrent = 0.0f;

private:
	
	FTimerHandle TimerHandle; // Timer descriptor
	float TimerRate = 1.0f;
	int32 MaxTimerCounter = 5;
	int32 TimerCounter = 0;

	void Move();

	// Function called by the timer
	void OnTimerFired();
	
};
