// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Key.h"
#include "Puzzle.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class HOUSEESCAPE_API APuzzle : public AInteractable
{
	GENERATED_BODY()
	
public:
	void SetIsSolved(bool isSolved);

	Puzzles GetPuzzleType();

	APuzzle();

protected:
	void BeginPlay() override;

	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<Rooms> roomPuzzleUnlocks;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<Puzzles> puzzleType;

	virtual void CheckSolution();

	bool isSolved;

	virtual void InitPuzzleState();
};
