// Fill out your copyright notice in the Description page of Project Settings.

#include "SaveGameUtil.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

void USaveGameUtil::CreateSaveGame()
{
	saveGameState = Cast<UHouseEscapeSaveGame>(UGameplayStatics::CreateSaveGameObject(UHouseEscapeSaveGame::StaticClass()));

	for (int i = Puzzles::WirePuzzle; i <= Puzzles::None; ++i)
	{
		Puzzles puzzle = static_cast<Puzzles>(i);
		saveGameState->puzzleStates.Add(puzzle, false);
	}

	UGameplayStatics::SaveGameToSlot(saveGameState, "SaveGame", 0);
}

void USaveGameUtil::Init(UMessenger* messengerRef)
{
	if (saveGameState == NULL)
	{
		saveGameState = (UHouseEscapeSaveGame*)UGameplayStatics::LoadGameFromSlot("SaveGame", 0);
	}

	if (saveGameState == NULL)
	{
		CreateSaveGame();
	}

	if (this->messenger == nullptr)
	{
		this->messenger = messengerRef;
		messenger->OnPuzzleSolved.AddDynamic(this, &USaveGameUtil::PuzzleSolved);
	}
}

UHouseEscapeSaveGame* USaveGameUtil::GetSaveGame()
{
	return saveGameState;
}

void USaveGameUtil::AddKey(Rooms keyToAdd)
{
	saveGameState->collectedKeys.Add(keyToAdd);
	UGameplayStatics::SaveGameToSlot(saveGameState, "SaveGame", 0);
}

bool USaveGameUtil::DoesPlayerHaveKey(Rooms key)
{
	return saveGameState->collectedKeys.Contains(key);
}

void USaveGameUtil::PuzzleSolved(FMessage message)
{
	TMap<TEnumAsByte<Puzzles>, bool> puzzleStates = saveGameState->puzzleStates;
	puzzleStates.Remove(message.puzzleType);
	puzzleStates.Add(message.puzzleType, true);
	saveGameState->puzzleStates = puzzleStates;
	UGameplayStatics::SaveGameToSlot(saveGameState, "SaveGame", 0);
}

bool USaveGameUtil::GetPuzzleState(Puzzles puzzle)
{
	if (saveGameState->puzzleStates.Find(puzzle) != nullptr)
	{
		return *saveGameState->puzzleStates.Find(puzzle);
	}

	return false;
}

TMap<TEnumAsByte<Puzzles>, bool> USaveGameUtil::GetPuzzleStates()
{
	return saveGameState->puzzleStates;
}