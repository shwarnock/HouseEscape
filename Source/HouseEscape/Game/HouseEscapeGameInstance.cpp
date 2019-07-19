// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseEscapeGameInstance.h"
#include "Kismet/GameplayStatics.h"

UHouseEscapeGameInstance::UHouseEscapeGameInstance()
{
	messenger = NewObject<UMessenger>();
	saveGame = NewObject<USaveGameUtil>();

	StartTime = FDateTime::Now();
}

UMessenger* UHouseEscapeGameInstance::GetMessenger()
{
	return messenger;
}

USaveGameUtil* UHouseEscapeGameInstance::GetSaveGameUtil()
{
	return saveGame;
}

void UHouseEscapeGameInstance::Shutdown()
{
	if (saveGame->GetSaveGame() == nullptr)
	{
		return;
	}

	FDateTime currentTime = FDateTime::Now();
	FTimespan duration = currentTime - StartTime;

	saveGame->AddPlayTime(duration);
}