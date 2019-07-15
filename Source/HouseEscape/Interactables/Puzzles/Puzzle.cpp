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
		messenger->AddInteractTarget(message);
	}
}

void APuzzle::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsPlayerOverlapping() && !isSolved)
	{
		FMessage message;
		message.interact = this;
		message.interactableType = interactType;
		messenger->RemoveInteractTarget(message);
	}
}

void APuzzle::BeginPlay()
{
	Super::BeginPlay();

	isSolved = saveGameUtil->GetPuzzleState(puzzleType);
	if (isSolved)
	{
		InitPuzzleState();
		if (!saveGameUtil->DoesPlayerHaveKey(roomPuzzleUnlocks))
		{
			FMessage message;
			message.room = roomPuzzleUnlocks;
			messenger->PuzzleSolved(message);
		}
	}
}

void APuzzle::SetIsSolved(bool solved)
{
	this->isSolved = solved;
	IsValidInteract = false;
}

Puzzles APuzzle::GetPuzzleType()
{
	return puzzleType;
}

void APuzzle::InitPuzzleState()
{
	IsValidInteract = false;
}

void APuzzle::CheckSolution()
{
}

void APuzzle::OnInteract_Implementation()
{
	//If we are not currently overlapping the box component, do not interact
	if (!AInteractable::BoxComponent->IsOverlappingComponent(UGameplayStatics::GetPlayerCharacter(AInteractable::GetWorld(), 0)->GetCapsuleComponent()))
	{
		return;
	}

	messenger->RemoveAllWidgets();
	APlayerController* playerController = AInteractable::GetWorld()->GetFirstPlayerController();

	//Toggle between player controller's camera and this camera when interact button is pressed
	if (playerController->GetViewTarget() == this)
	{
		playerController->SetViewTargetWithBlend((AActor*)UGameplayStatics::GetPlayerCharacter(AInteractable::GetWorld(), 0), 0.5f);
		playerController->bEnableMouseOverEvents = false;
		playerController->bShowMouseCursor = false;
		playerController->bEnableClickEvents = false;
		AInteractable::StaticMeshComponent->SetRenderCustomDepth(true);

		FMessage message;
		message.interact = this;
		messenger->CollideWithInteractable(message);

		playerController->SetInputMode(FInputModeGameOnly());
	}
	else
	{
		playerController->SetViewTargetWithBlend((AActor*)this, 0.5f);
		playerController->bEnableMouseOverEvents = true;
		playerController->bShowMouseCursor = true;
		playerController->bEnableClickEvents = true;
		AInteractable::StaticMeshComponent->SetRenderCustomDepth(false);

		playerController->SetInputMode(FInputModeGameAndUI());
	}
}