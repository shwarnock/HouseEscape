#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum Rooms
{
	BasementFrontCenterRoom = 0,
	BasementFrontRight = 1,
	BasementBackLeftRoom = 2
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
	None = 3
};