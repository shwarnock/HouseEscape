// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleBoard.h"

APuzzleBoard::APuzzleBoard()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BasicCube(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BackgroundMaterial(TEXT("/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass"));
	
	StaticMeshComponent->SetStaticMesh(BasicCube.Object);
	StaticMeshComponent->SetMaterial(0, BackgroundMaterial.Object);

	UPuzzleBoardPieceComponent::ResetIndex();

	PuzzlePieceA = CreateDefaultSubobject<UPuzzleBoardPieceComponent>(TEXT("PuzzlePieceA"));
	PuzzlePieceB = CreateDefaultSubobject<UPuzzleBoardPieceComponent>(TEXT("PuzzlePieceB"));
	PuzzlePieceC = CreateDefaultSubobject<UPuzzleBoardPieceComponent>(TEXT("PuzzlePieceC"));

	PuzzlePieceA->SetupAttachment(RootComponent);
	PuzzlePieceB->SetupAttachment(RootComponent);
	PuzzlePieceC->SetupAttachment(RootComponent);

	//Setup Camera Components
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);

	puzzleType = Puzzles::PuzzleBoard;
	roomPuzzleUnlocks = Rooms::BasementCenterRoom;
}

void APuzzleBoard::BeginPlay()
{
	Super::BeginPlay();

	PuzzlePieceA->CheckSolution.AddDynamic(this, &APuzzleBoard::CheckSolution);
	PuzzlePieceB->CheckSolution.AddDynamic(this, &APuzzleBoard::CheckSolution);
	PuzzlePieceC->CheckSolution.AddDynamic(this, &APuzzleBoard::CheckSolution);
}

void APuzzleBoard::CheckSolution()
{	
	if (PuzzlePieceA->GetIsSlotted() && PuzzlePieceB->GetIsSlotted() && PuzzlePieceC->GetIsSlotted())
	{
		PuzzleCompleted();
	}
}