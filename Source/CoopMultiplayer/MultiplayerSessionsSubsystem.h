// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "MultiplayerSessionsSubsystem.generated.h"


/**
 * 
 */
UCLASS()
class COOPMULTIPLAYER_API UMultiplayerSessionsSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UMultiplayerSessionsSubsystem();

	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

	IOnlineSessionPtr SessionInterface;

	UFUNCTION(BlueprintCallable)
	void CreateServer(FString ServerName /* bool bIsLAN, int32 MaxNumPlayers */);
	
	UFUNCTION(BlueprintCallable)
	void FindServers(FString ServerName);

	void OnCreateSessionComplete(FName SessionName, bool WasSuccessful);

	void OnDestroySessionComplete(FName SessionName, bool WasSuccessful);

	bool CreateServerAfterDestroy;

	FString DestroyServerName;
	
};
