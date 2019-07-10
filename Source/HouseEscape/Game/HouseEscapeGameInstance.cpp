// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseEscapeGameInstance.h"
#include "Kismet/GameplayStatics.h"

UHouseEscapeGameInstance::UHouseEscapeGameInstance()
{
	messenger = NewObject<UMessenger>();
	saveGame = NewObject<USaveGameUtil>();
}

UMessenger* UHouseEscapeGameInstance::GetMessenger()
{
	return messenger;
}

USaveGameUtil* UHouseEscapeGameInstance::GetSaveGameUtil()
{
	return saveGame;
}