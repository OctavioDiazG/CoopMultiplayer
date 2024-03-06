// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"


void PrintString(const FString& String)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Cyan, String);
	}
}

UMultiplayerSessionsSubsystem::UMultiplayerSessionsSubsystem()
{
	//PrintString("MSS Constructor Called!");
}

void UMultiplayerSessionsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//PrintString("MSS Initialize!");

	IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get();
	if (OnlineSubsystem)
	{
		FString SubsystemName = OnlineSubsystem->GetSubsystemName().ToString();
		PrintString("Online Subsystem: " + SubsystemName);

		SessionInterface = OnlineSubsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			PrintString("Session Interface Valid!");
		}
	}
}

void UMultiplayerSessionsSubsystem::Deinitialize()
{
	//UE_LOG(LogTemp, Warning, TEXT("MSS Deinitialize!"));
	
}

void UMultiplayerSessionsSubsystem::CreateServer(FString ServerName)
{
	PrintString("Create Server");
	if (ServerName.IsEmpty())
	{
		PrintString("Server Cannot be Empty");
		return;
	}
	FName MySessionName = FName("Coop Adventure Session Name");
	
	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true; // Allow players to join a game in progress
	SessionSettings.bIsDedicated = false; // Is this a dedicated server?
	SessionSettings.bShouldAdvertise = true; // Should this session be place in the servers list?
	SessionSettings.NumPublicConnections = 2; // Number of public connections allowed 
	SessionSettings.bUseLobbiesIfAvailable = true; // Use lobbies if available
	SessionSettings.bUsesPresence = true; // Use presence for this session
	SessionSettings.bAllowJoinViaPresence = true; // Allow invites to this session
	
	bool IsLAN = false;
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		IsLAN = true;
	}
	
	SessionSettings.bIsLANMatch = IsLAN; // this value will depend if we are using the OnlineSubsystemNull or OnlineSubsystemSteam if Null we are using LAN
	
	SessionInterface->CreateSession(0, MySessionName, SessionSettings);
}

void UMultiplayerSessionsSubsystem::FindServers(FString ServerName)
{
	PrintString("Find Servers");
}

