#pragma once

#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum Rooms
{
	BasementFrontRight
};

UENUM(BlueprintType)
enum Interacts
{
	Door,
	Key,
	Puzzle,
	LightSwitch,
	Item
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
	None = 1
};