// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleBoard.h"

APuzzleBoard::APuzzleBoard()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BasicCube(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> BackgroundMaterial(TEXT("/Game/StarterContent/Materials/M_Ground_Grass.M_Ground_Grass"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TranslucentCube(TEXT("/Game/StaticMeshes/TestMeshes/TranslucentCube.TranslucentCube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TranslucentPyramid(TEXT("/Game/StaticMeshes/TestMeshes/TranslucentPyramid.TranslucentPyramid"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TranslucentCylinder(TEXT("/Game/StaticMeshes/TestMeshes/TranslucentCylinder.TranslucentCylinder"));

	StaticMeshComponent->SetStaticMesh(BasicCube.Object);
	StaticMeshComponent->SetMaterial(0, BackgroundMaterial.Object);

	PuzzlePieceA = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzlePieceA"));
	PuzzlePieceB = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzlePieceB"));
	PuzzlePieceC = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuzzlePieceC"));

	PuzzlePieceA->SetStaticMesh(TranslucentCube.Object);
	PuzzlePieceA->SetupAttachment(RootComponent);

	PuzzlePieceB->SetStaticMesh(TranslucentCylinder.Object);
	PuzzlePieceB->SetupAttachment(RootComponent);

	PuzzlePieceC->SetStaticMesh(TranslucentPyramid.Object);
	PuzzlePieceC->SetupAttachment(RootComponent);

	//Setup Camera Components
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(RootComponent);

	puzzleType = Puzzles::PuzzleBoard;
}