// Copyright Epic Games, Inc. All Rights Reserved.


#include "GamePracticeGameModeBase.h"
#include "BasePawn.h"

AGamePracticeGameModeBase::AGamePracticeGameModeBase()
{
	DefaultPawnClass = ABasePawn::StaticClass();
}

