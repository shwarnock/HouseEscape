// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Puzzles/Puzzle.h"
#include "VentPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API AVentPuzzle : public APuzzle
{
	GENERATED_BODY()

	//Screw Meshes
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TopLeftScrew;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TopRightScrew;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BottomLeftScrew;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BottomRightScrew;
	
public:
	AVentPuzzle();

private:
	UFUNCTION()
	void HandleComponentClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	int screwCount;

	void InitPuzzleState() override;
};
