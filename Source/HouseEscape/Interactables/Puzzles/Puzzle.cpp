// Fill out your copyright notice in the Description page of Project Settings.

#include "Puzzle.h"

APuzzle::APuzzle()
{
	isSolved = false;
	interactType = Interacts::Puzzle;
}

void APuzzle::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(IsPlayerOverlapping() && !isSolved)
	{
		FMessage message;
		message.interact = this;
		message.interactableType = interactType;
		message.uniqueId =  uniqueId;
		messenger->CollideWithInteractable(message);
		messenger->AddInteractTarget(message);
	}
}

void APuzzle::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsPlayerOverlapping())
	{
		FMessage message;
		message.interact = this;
		message.interactableType = interactType;
		messenger->EndCollideWithInteractable(message);
		messenger->RemoveInteractTarget(message);
	}
}

void APuzzle::BeginPlay()
{
	Super::BeginPlay();
}

void APuzzle::SetIsSolved(bool solved)
{
	this->isSolved = solved;
}

Puzzles APuzzle::GetPuzzleType()
{
	return puzzleType;
}

void APuzzle::InitPuzzleState()
{
}

void APuzzle::CheckSolution()
{
}