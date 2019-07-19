// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "ItemStruct.h"
#include "GameFramework/SaveGame.h"
#include "HouseEscapeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API UHouseEscapeSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<TEnumAsByte<Rooms>> collectedKeys;

	UPROPERTY()
	TMap<TEnumAsByte<Puzzles>, bool> puzzleStates;

	UPROPERTY()
	float TotalPlayTime;

	UPROPERTY()
	TArray<FItem> items;
};
