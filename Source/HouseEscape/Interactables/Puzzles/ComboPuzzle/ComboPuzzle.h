// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Puzzles/Puzzle.h"
#include "ComboPuzzleComp.h"
#include "ComboPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API AComboPuzzle : public APuzzle
{
	GENERATED_BODY()

	int meshCount = 6;

	AComboPuzzle();

	UPROPERTY(EditAnywhere)
	UComboPuzzleComp* PuzzlePiece;

	UPROPERTY(EditAnywhere)
	UComboPuzzleComp* PuzzlePiece2;

	UPROPERTY(EditAnywhere)
	UComboPuzzleComp* PuzzlePiece3;

	UPROPERTY(EditAnywhere)
	UComboPuzzleComp* PuzzlePiece4;

	UPROPERTY(EditAnywhere)
	UComboPuzzleComp* PuzzlePiece5;

	UPROPERTY(EditAnywhere)
	UComboPuzzleComp* PuzzlePiece6;

	UPROPERTY(EditAnywhere)
	UComboPuzzleComp* PuzzlePiece7;

private:
	void OnInteract_Implementation() override;

	UComboPuzzleComp* currentInteraction;

	TArray<UComboPuzzleComp*> puzzleInteractionOrder;
	TArray<int> puzzleSolution;

	UFUNCTION()
	void HandlePuzzleCompOverlap(FMessage message);

	UFUNCTION()
	void HandlePuzzleCompEndOverlap(FMessage message);

	void BeginPlay() override;

	void CheckSolution() override;
};
