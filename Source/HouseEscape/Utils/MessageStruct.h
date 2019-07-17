#pragma once

#include "CoreMinimal.h"
#include "Enums.h"
#include "ItemStruct.h"
#include "Components/StaticMeshComponent.h"
#include "MessageStruct.generated.h"

class AInteractable;

USTRUCT(BlueprintType)
struct FMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<Interacts> interactableType;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<Rooms> room;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<DoorStates> doorState;

	UPROPERTY()
	TEnumAsByte<Puzzles> puzzleType;

	UPROPERTY(BlueprintReadWrite)
	FItem itemInfo;

	UPROPERTY()
	FGuid uniqueId;

	UPROPERTY()
	AInteractable* interact;

	UPROPERTY(BlueprintReadWrite)
	TArray<FItem> items;
};
