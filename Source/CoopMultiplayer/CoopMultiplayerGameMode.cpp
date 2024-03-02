// Copyright Epic Games, Inc. All Rights Reserved.

#include "CoopMultiplayerGameMode.h"
#include "CoopMultiplayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACoopMultiplayerGameMode::ACoopMultiplayerGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
