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

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Grate;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Top;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Left;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Right;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Bottom;

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;
	
public:
	AVentPuzzle();

protected:
	UFUNCTION()
	void HandleScrewComponentClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	void BeginPlay() override;

private:

	int screwCount;

	void InitPuzzleState() override;

	void CheckSolution() override;
};
