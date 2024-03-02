// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CoopMultiplayerGameMode.generated.h"

UCLASS(minimalapi)
class ACoopMultiplayerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACoopMultiplayerGameMode();

	UFUNCTION(BlueprintCallable)
	void HostLANGame();

	UFUNCTION(BlueprintCallable)
	void JoinLANGame();
};



