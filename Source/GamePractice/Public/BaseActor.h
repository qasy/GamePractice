// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UENUM(BlueprintType)
enum class EMovementType : uint8
{
	Static,
	Sin
};

USTRUCT(BlueprintType)
struct FMovementData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	FVector InitialLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Amplitude = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Frequency = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	EMovementType MovementType = EMovementType::Sin;
};


UCLASS()
class GAMEPRACTICE_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

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
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetColor(const FLinearColor& Color);
	void SetMovementData(const FMovementData& MData);

private:
	void Move();
	
};
