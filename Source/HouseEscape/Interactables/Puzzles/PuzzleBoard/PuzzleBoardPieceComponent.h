// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Materials/MaterialInterface.h"
#include "Components/StaticMeshComponent.h"
#include "Delegates/Delegate.h"
#include "ItemStruct.h"
#include "PuzzleBoardPieceComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCheckPuzzleSolution);

UCLASS()
class HOUSEESCAPE_API UPuzzleBoardPieceComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPuzzleBoardPieceComponent();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	bool GetIsSlotted();

	UPROPERTY()
	FCheckPuzzleSolution CheckSolution;

	static void ResetIndex();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void HandleMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void HandleEndMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void HandleClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UMaterialInterface* HoverMaterial;
	UMaterialInterface* StaticMaterial;
	UMaterialInterface* SlottedMaterial;
	
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ItemType> itemType;

	bool isSlotted;

	static int index;
};
