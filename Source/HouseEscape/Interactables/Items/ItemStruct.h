#pragma once

#include "Components/StaticMeshComponent.h"
#include "ItemStruct.generated.h"

class AItemBase;

UENUM(BlueprintType)
enum ItemType
{
	Screwdriver
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AItemBase* baseClass;
};