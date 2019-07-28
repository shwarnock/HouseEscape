// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Puzzles/Puzzle.h"
#include "PuzzleBoard.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API APuzzleBoard : public APuzzle
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PuzzlePieceA;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PuzzlePieceB;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PuzzlePieceC;
	
	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

	APuzzleBoard();
};
