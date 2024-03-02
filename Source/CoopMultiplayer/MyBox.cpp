// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBox.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AMyBox::AMyBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ReplicatedVar = 100.0f;

}

// Called when the game starts or when spawned
void AMyBox::BeginPlay()
{
	Super::BeginPlay();

	SetReplicates(true);
	SetReplicateMovement(true);
	
#if 0
	if(HasAuthority())
	{
		//print if its the server
		GEngine->AddOnScreenDebugMessage( -1, 10.f, FColor::Green, TEXT("Server"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage( -1, 10.f, FColor::Red, TEXT("Client"));
	}
#endif
	
}

// Called every frame
void AMyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyBox::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyBox, ReplicatedVar);
}

