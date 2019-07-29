#pragma once

#include "Components/StaticMeshComponent.h"
#include "ItemStruct.generated.h"

class AItemBase;

UENUM(BlueprintType)
enum ItemType
{
	Screwdriver,
	PuzzlePieceA,
	PuzzlePieceB,
	PuzzlePieceC,
	Empty
};

USTRUCT(BlueprintType)
struct FItem
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ItemType> itemType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* texture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int itemIndex;

	bool operator == (FItem const& item)
	{
		if (this->itemIndex == item.itemIndex && 
			this->itemType == item.itemType && 
			this->name.EqualTo(item.name) && 
			this->texture == item.texture)
		{
			return true;
		}

		return false;
	}
};