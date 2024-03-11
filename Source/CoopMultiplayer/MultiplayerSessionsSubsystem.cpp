// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerSessionsSubsystem.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"


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

	CreateServerAfterDestroy = false;
	DestroyServerName = "";
	ServerNameToFind = "";
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
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnCreateSessionComplete );
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UMultiplayerSessionsSubsystem::OnFindSessionsComplete);
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

	FNamedOnlineSession *ExistingSessions = SessionInterface->GetNamedSession(MySessionName);
	if (ExistingSessions)
	{
		PrintString(" Destroying Session ");
		CreateServerAfterDestroy = true;
		DestroyServerName = ServerName;
		SessionInterface->DestroySession(MySessionName);
		return;
	}
	
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

	SessionSettings.Set(FName("SERVER_NAME"), ServerName, EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);
	
	SessionInterface->CreateSession(0, MySessionName, SessionSettings);
}

void UMultiplayerSessionsSubsystem::FindServers(FString ServerName)
{
	PrintString("Find Servers");
	if (ServerName.IsEmpty())
	{
		PrintString("Server Cannot be Empty");
		return;
	}
	
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	bool IsLAN = false;
	if (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL")
	{
		IsLAN = true;
	}
	SessionSearch->bIsLanQuery = IsLAN;
	SessionSearch->MaxSearchResults = 9999;
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	ServerNameToFind = ServerName;

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

void UMultiplayerSessionsSubsystem::OnCreateSessionComplete(FName SessionName, bool WasSuccessful)
{
	if (WasSuccessful)
	{
		GetWorld()->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
	}
	else
	{
		PrintString("Session Creation Failed");
	}
}

void UMultiplayerSessionsSubsystem::OnDestroySessionComplete(FName SessionName, bool WasSuccessful)
{
	PrintString("On Destroy Session Complete");

	if (CreateServerAfterDestroy)
	{
		CreateServerAfterDestroy = false;
		CreateServer(DestroyServerName);
	}
}

void UMultiplayerSessionsSubsystem::OnFindSessionsComplete(bool WasSuccessful)
{
	if (!WasSuccessful)
	{
		return;
	}
	if (ServerNameToFind.IsEmpty())
	{
		return;
	}

	TArray <FOnlineSessionSearchResult> Results = SessionSearch->SearchResults;

	if (Results.Num() > 0)
	{
		FString Msg = "Found " + FString::FromInt(Results.Num()) + " Sessions";
		PrintString(Msg);

		for (FOnlineSessionSearchResult Result : Results)
		{
			if (Result.IsValid())
			{
				FString SessionID = Result.GetSessionIdStr();
				FString ServerName = "No-Name";
				Result.Session.SessionSettings.Get(FName("SERVER_NAME"), ServerName);
				Msg = " Server Name: " + ServerName + " SessionID: " + SessionID;
				PrintString(Msg);
			}
			
		}
	}
	else
	{
		PrintString("Zero Sessions Found!");
	}
}



