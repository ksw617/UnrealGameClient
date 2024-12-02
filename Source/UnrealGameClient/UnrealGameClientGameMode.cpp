// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealGameClientGameMode.h"
#include "UnrealGameClientCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUnrealGameClientGameMode::AUnrealGameClientGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
