// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "SelfDrivingCarGameMode.h"
#include "SelfDrivingCarCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASelfDrivingCarGameMode::ASelfDrivingCarGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
