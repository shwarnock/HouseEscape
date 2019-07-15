// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Puzzle.h"
#include "InputCoreTypes.h"
#include "WirePuzzleMeshComponent.h"
#include "WirePuzzle.generated.h"

UCLASS()
class HOUSEESCAPE_API AWirePuzzle : public APuzzle
{
	GENERATED_BODY()

	UPROPERTY()
	UWirePuzzleMeshComponent* BlueA;

	UPROPERTY()
	UWirePuzzleMeshComponent* BlueB;

	UPROPERTY()
	UWirePuzzleMeshComponent* YellowA;

	UPROPERTY()
	UWirePuzzleMeshComponent* YellowB;

	UPROPERTY()
	UWirePuzzleMeshComponent* RedA;

	UPROPERTY()
	UWirePuzzleMeshComponent* RedB;

	UPROPERTY()
	UWirePuzzleMeshComponent* GreenA;

	UPROPERTY()
	UWirePuzzleMeshComponent* GreenB;

public:
	AWirePuzzle();

private:
	enum Colors
	{
		None   = 0,
		Blue   = 1,
		Green  = 2,
		Yellow = 3,
		Red    = 4
	};

	TArray<Colors> currentPuzzleState;

	TArray<Colors> puzzleSolution;

	UMaterialInterface* GreenMaterial;
	UMaterialInterface* RedMaterial;
	UMaterialInterface* YellowMaterial;
	UMaterialInterface* BlueMaterial;

	void CheckSolution();

	void SetWireComponentColor(UWirePuzzleMeshComponent* wireComponent, Colors color);

protected:

	UFUNCTION()
	void HandleComponentClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void InitPuzzleState() override;

	void BeginPlay() override;
};
