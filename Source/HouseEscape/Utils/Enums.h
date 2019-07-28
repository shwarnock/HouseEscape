#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum Rooms
{
	BasementFrontCenterRoom = 0,
	BasementFrontRight = 1,
	BasementBackLeftRoom = 2,
	BasementCenterRoom = 3,
	BasementFrontLeftRoom = 4
};

UENUM(BlueprintType)
enum Interacts
{
	Door,
	Key,
	Puzzle,
	LightSwitch,
	Item,
	Generic
};

UENUM(BlueprintType)
enum DoorStates
{
	NoKey,
	Closed,
	Open
};

UENUM(BlueprintType)
enum Puzzles
{
	WirePuzzle = 0,
	VentPuzzle = 1,
	WindowPuzzle = 2,
	ComboPuzzle = 3,
	PuzzleBoard = 4,
	None = 5
};