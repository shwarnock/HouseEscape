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

	SaveGame();
}

void USaveGameUtil::Init(UMessenger* messengerRef)
{
	if (SaveGameName.IsEmpty())
	{
		SaveGameName = "EditorGame";
	}

	if (saveGameState == NULL)
	{
		saveGameState = (UHouseEscapeSaveGame*)UGameplayStatics::LoadGameFromSlot(SaveGameName, 0);
	}

	if (saveGameState == NULL)
	{
		CreateSaveGame();
	}

	if (this->messenger == nullptr)
	{
		this->messenger = messengerRef;
		messenger->OnPuzzleSolved.AddDynamic(this, &USaveGameUtil::PuzzleSolved);
		messenger->OnItemPickedUp.AddDynamic(this, &USaveGameUtil::HandleItemPickedUp);
		messenger->OnItemRemoved.AddDynamic(this, &USaveGameUtil::HandleItemRemoved);
	}
}

UHouseEscapeSaveGame* USaveGameUtil::GetSaveGame()
{
	return saveGameState;
}

void USaveGameUtil::AddKey(Rooms keyToAdd)
{
	saveGameState->collectedKeys.Add(keyToAdd);
	SaveGame();
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
	SaveGame();
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

void USaveGameUtil::SetSaveGameName(FString name)
{
	SaveGameName = name;
}

void USaveGameUtil::DeleteSaveGame(FString name)
{
	UGameplayStatics::DeleteGameInSlot(SaveGameName, 0);
}

void USaveGameUtil::AddPlayTime(FTimespan duration)
{
	saveGameState->TotalPlayTime += duration.GetTotalSeconds();
	SaveGame();
}

void USaveGameUtil::SaveGame()
{
	UGameplayStatics::SaveGameToSlot(saveGameState, SaveGameName, 0);
}

FString USaveGameUtil::GetTotalPlayTime(FString name)
{
	UHouseEscapeSaveGame* game = (UHouseEscapeSaveGame*) UGameplayStatics::LoadGameFromSlot(name, 0);
	if (!game)
	{
		return "00:00:00:00";
	}

	FTimespan playTimespan = FTimespan::FromSeconds(game->TotalPlayTime);
	FString playTime = "";

	if (playTimespan.GetDays() < 10)
	{
		playTime.Append("0");
	}

	playTime.Append(FString::FromInt(playTimespan.GetDays()));
	playTime.Append(":");

	if (playTimespan.GetHours() < 10)
	{
		playTime.Append("0");
	}

	playTime.Append(FString::FromInt(playTimespan.GetHours()));
	playTime.Append(":");

	if (playTimespan.GetMinutes() < 10)
	{
		playTime.Append("0");
	}

	playTime.Append(FString::FromInt(playTimespan.GetMinutes()));
	playTime.Append(":");

	if (playTimespan.GetSeconds() < 10)
	{
		playTime.Append("0");
	}

	playTime.Append(FString::FromInt(playTimespan.GetSeconds()));

	return playTime;
}

void USaveGameUtil::HandleItemPickedUp(FMessage message)
{
	saveGameState->items.Add(message.itemInfo);
	SaveGame();
}

bool USaveGameUtil::DoesPlayHaveItem(FItem item)
{
	int count = saveGameState->items.Num();
	for (int i = 0; i < count; ++i)
	{
		if (saveGameState->items[i].itemType == item.itemType)
		{
			return true;
		}
	}

	return false;
}

void USaveGameUtil::HandleItemRemoved(FMessage message)
{
	saveGameState->items.Remove(message.itemInfo);
	SaveGame();
}