// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Interactable.h"
#include "ItemStruct.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API AItemBase : public AInteractable
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnInteract();
	void OnInteract_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItem itemInfo;

	void BeginPlay() override;

public:
	AItemBase();

	static FItem EmptyItem();
};
