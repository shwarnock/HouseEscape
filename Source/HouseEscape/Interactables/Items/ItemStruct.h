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

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* meshComponent;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ItemType> itemType;

	UPROPERTY(EditAnywhere)
	UTexture2D* texture;

	UPROPERTY(EditAnywhere)
	FName name;

	UPROPERTY(EditAnywhere)
	int itemIndex;

	UPROPERTY(EditAnywhere)
	AItemBase* baseClass;
};