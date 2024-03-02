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

void ACoopMultiplayerGameMode::HostLANGame()
{
	GetWorld()->ServerTravel("Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void ACoopMultiplayerGameMode::JoinLANGame()
{
	APlayerController *PC = GetGameInstance()->GetFirstLocalPlayerController();
	if (PC)
	{
		PC->ClientTravel("192.168.100.82" /*IP Address of the host*/, ETravelType::TRAVEL_Absolute);
	}
}
