#include "ComboPuzzle.h"

AComboPuzzle::AComboPuzzle()
{
	PuzzlePiece = CreateDefaultSubobject<UComboPuzzleComp>(TEXT("PuzzlePiece"));
	PuzzlePiece2 = CreateDefaultSubobject<UComboPuzzleComp>(TEXT("PuzzlePiece2"));
	PuzzlePiece3 = CreateDefaultSubobject<UComboPuzzleComp>(TEXT("PuzzlePiece3"));
	PuzzlePiece4 = CreateDefaultSubobject<UComboPuzzleComp>(TEXT("PuzzlePiece4"));
	PuzzlePiece5 = CreateDefaultSubobject<UComboPuzzleComp>(TEXT("PuzzlePiece5"));
	PuzzlePiece6 = CreateDefaultSubobject<UComboPuzzleComp>(TEXT("PuzzlePiece6"));
	PuzzlePiece7 = CreateDefaultSubobject<UComboPuzzleComp>(TEXT("PuzzlePiece7"));
	PuzzlePiece7->ToggleVisibility(true);
	PuzzlePiece7->ToggleActive();

	TArray<UComboPuzzleComp*> components;
	GetComponents<UComboPuzzleComp>(components);

	TArray<int> puzzleNums = {0, 1, 2, 3, 4, 5};
	puzzleSolution = puzzleNums;

	for (int i = 0; i < components.Num() - 1; ++i)
	{
		UComboPuzzleComp* CurrentComp = components[i];
		CurrentComp->SetupAttachment(StaticMeshComponent);
		
		int randomNum = FMath::RandRange(0, puzzleNums.Num() - 1);
		int numToUse = puzzleNums[randomNum];
		CurrentComp->SetPuzzleIndex(puzzleNums[randomNum]);
		puzzleNums.Remove(numToUse);
	}

	puzzleInteractionOrder.Empty();

	int32 LastIndex = puzzleSolution.Num() - 1;
	for (int32 i = 0; i <= LastIndex; ++i)
	{
		int32 Index = FMath::RandRange(i, LastIndex);
		if (i != Index)
		{
			puzzleSolution.Swap(i, Index);
		}
	}

	puzzleType = Puzzles::ComboPuzzle;
}

void AComboPuzzle::OnInteract_Implementation()
{
	if (puzzleInteractionOrder.Num() == 6)
	{
		for (UComboPuzzleComp* comp : puzzleInteractionOrder)
		{
			comp->SetPieceMaterial(UComboPuzzleComp::NotSelected);
			comp->SetText(FText());
		}

		puzzleInteractionOrder.Empty();
	}

	UComboPuzzleComp* comp = Cast<UComboPuzzleComp>(currentInteraction);
	if (puzzleInteractionOrder.Num() < 6 && !puzzleInteractionOrder.Contains(comp))
	{
		puzzleInteractionOrder.Add(comp);
		comp->SetText(FText::FromString(*FString::FromInt(puzzleInteractionOrder.Num())));
		comp->SetPieceMaterial(UComboPuzzleComp::Selected);
	}

	if (puzzleInteractionOrder.Num() == 6)
	{
		CheckSolution();
	}
}

void AComboPuzzle::BeginPlay()
{
	Super::BeginPlay();

	messenger->OnOverlapPuzzleComp.AddDynamic(this, &AComboPuzzle::HandlePuzzleCompOverlap);
	messenger->OnEndOverlapPuzzleComp.AddDynamic(this, &AComboPuzzle::HandlePuzzleCompEndOverlap);
}

void AComboPuzzle::HandlePuzzleCompOverlap(FMessage message)
{
	if (isSolved || !IsPlayerOverlapping())
	{
		return;
	}

	currentInteraction = message.comp;
	meshToRender = currentInteraction->mesh;
	
	message.interact = this;
	message.interactableType = interactType;
	messenger->AddInteractTarget(message);
}

void AComboPuzzle::HandlePuzzleCompEndOverlap(FMessage message)
{
	if (IsPlayerOverlapping() || isSolved)
	{
		return;
	}
	message.interact = this;
	message.interactableType = interactType;
	messenger->RemoveInteractTarget(message);
	meshToRender = nullptr;
	currentInteraction = nullptr;
}

void AComboPuzzle::CheckSolution()
{
	bool puzzleSolved = true;
	for (int i = 0; i < puzzleInteractionOrder.Num(); i++)
	{
		if (puzzleInteractionOrder[i]->GetPuzzleIndex() == puzzleSolution[i])
		{
			puzzleInteractionOrder[i]->SetPieceMaterial(UComboPuzzleComp::Correct);
		}
		else
		{
			puzzleInteractionOrder[i]->SetPieceMaterial(UComboPuzzleComp::Incorrect);
			puzzleSolved = false;
		}
	}

	if (puzzleSolved)
	{
		PuzzleCompleted();
	}
}