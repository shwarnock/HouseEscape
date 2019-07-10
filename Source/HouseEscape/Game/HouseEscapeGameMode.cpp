// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HouseEscapeGameMode.h"
#include "HouseEscapeCharacter.h"
#include "HouseEscapeGameInstance.h"
#include "Engine.h"

AHouseEscapeGameMode::AHouseEscapeGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AHouseEscapeCharacter::StaticClass();
}

void AHouseEscapeGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetWorld()->GetName() == FString("BackgroundLevel"))
	{
		UHouseEscapeGameInstance* gameInstance = Cast<UHouseEscapeGameInstance>(GetWorld()->GetGameInstance());
		gameInstance->GetSaveGameUtil()->Init(gameInstance->GetMessenger());
	}
}