// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "Messenger.h"
#include "UObject/NoExportTypes.h"
#include "HouseEscapeSaveGame.h"
#include "SaveGameUtil.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class HOUSEESCAPE_API USaveGameUtil : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UHouseEscapeSaveGame* saveGameState;

	UMessenger* messenger;

	void InitDoorStates();

public:
	void CreateSaveGame();
	void Init(UMessenger* messengerRef);

	UHouseEscapeSaveGame* GetSaveGame();

	void AddKey(Rooms keyToAdd);

	UFUNCTION(BlueprintCallable)
	bool DoesPlayerHaveKey(Rooms key);

	UFUNCTION()
	void PuzzleSolved(FMessage message);

	UFUNCTION()
	bool GetPuzzleState(Puzzles puzzle);

	UFUNCTION(BlueprintCallable)
	TMap<TEnumAsByte<Puzzles>, bool> GetPuzzleStates();
};
