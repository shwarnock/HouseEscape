// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Puzzles/Puzzle.h"
#include "PuzzleBoardPieceComponent.h"
#include "PuzzleBoard.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API APuzzleBoard : public APuzzle
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UPuzzleBoardPieceComponent* PuzzlePieceA;

	UPROPERTY(EditAnywhere)
	UPuzzleBoardPieceComponent* PuzzlePieceB;

	UPROPERTY(EditAnywhere)
	UPuzzleBoardPieceComponent* PuzzlePieceC;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	APuzzleBoard();

private:
	void BeginPlay() override;

	UFUNCTION()
	void CheckSolution() override;
};
