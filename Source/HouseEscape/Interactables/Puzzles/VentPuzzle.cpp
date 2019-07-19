// Fill out your copyright notice in the Description page of Project Settings.

#include "VentPuzzle.h"
#include "ItemBase.h"
#include "HouseEscapeCharacter.h"

AVentPuzzle::AVentPuzzle()
{
	//Create ScrewHeads
	TopLeftScrew = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopLeftScrew"));
	TopRightScrew = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopRightScrew"));
	BottomLeftScrew = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomLeftScrew"));
	BottomRightScrew = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomRightScrew"));
	Grate = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grate"));
	Top = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Top"));
	Left = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Right = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Bottom = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bottom"));

	TopLeftScrew->ComponentTags.Add("Screw");
	TopRightScrew->ComponentTags.Add("Screw");
	BottomRightScrew->ComponentTags.Add("Screw");
	BottomLeftScrew->ComponentTags.Add("Screw");

	TArray<UActorComponent*> components = GetComponentsByTag(UStaticMeshComponent::StaticClass(), "Screw");

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ScrewMesh(TEXT("/Game/StaticMeshes/Items/ScrewHead.ScrewHead"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> GrateMesh(TEXT("/Game/StaticMeshes/AirVent/Grate.Grate"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));

	//Setup Components
	int componentCount = components.Num();
	for (int i = 0; i < componentCount; ++i)
	{
		UStaticMeshComponent* component = (UStaticMeshComponent*) components[i];
		component->SetStaticMesh(ScrewMesh.Object);
		component->SetupAttachment(RootComponent);
		component->SetWorldScale3D(FVector(0.03f, 0.03f, 0.03f));
		component->SetRelativeRotation(FRotator(180, 180, 270));
	}

	TopLeftScrew->SetRelativeLocation(FVector(-59, 22, 31));
	TopRightScrew->SetRelativeLocation(FVector(31, 22, 31));
	BottomLeftScrew->SetRelativeLocation(FVector(-59, 22, -8));
	BottomRightScrew->SetRelativeLocation(FVector(31, 22, -8));

	Grate->SetStaticMesh(GrateMesh.Object);
	Grate->SetupAttachment(RootComponent);
	Grate->SetRelativeLocation(FVector(0, 15, 0));
	Grate->SetWorldRotation(FRotator(180, 0, 90));
	Grate->SetRelativeScale3D(FVector(0.5, 0.25, 1));

	Top->SetStaticMesh(CubeMesh.Object);
	Top->SetupAttachment(RootComponent);
	Top->SetRelativeLocation(FVector(0, 10, 20));
	Top->SetRelativeScale3D(FVector(1, 0.1, 0.1));

	Bottom->SetStaticMesh(CubeMesh.Object);
	Bottom->SetupAttachment(RootComponent);
	Bottom->SetRelativeLocation(FVector(0, 10, -20));
	Bottom->SetRelativeScale3D(FVector(1, 0.1, 0.1));

	Left->SetStaticMesh(CubeMesh.Object);
	Left->SetupAttachment(RootComponent);
	Left->SetRelativeLocation(FVector(-45, 10, 0));
	Left->SetRelativeScale3D(FVector(0.1, 0.1, 0.3));
	
	Right->SetStaticMesh(CubeMesh.Object);
	Right->SetupAttachment(RootComponent);
	Right->SetRelativeLocation(FVector(45, 10, 0));
	Right->SetRelativeScale3D(FVector(0.1, 0.1, 0.3));

	puzzleType = Puzzles::VentPuzzle;

	screwCount = 4;

	//Setup Camera Components
	CameraComponent = AInteractable::CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(AInteractable::RootComponent);
	CameraComponent->SetRelativeLocation(FVector(0, 100, 0));
	CameraComponent->SetRelativeRotation(FRotator(180, 90, 180));

	meshToRender = TopLeftScrew;

	BoxComponent->SetBoxExtent(FVector(80, 80, 32));
	BoxComponent->SetRelativeLocation(FVector(0, 70, 0));
}

void AVentPuzzle::BeginPlay()
{
	Super::BeginPlay();


	TopLeftScrew->OnClicked.AddDynamic(this, &AVentPuzzle::HandleScrewComponentClicked);
	TopRightScrew->OnClicked.AddDynamic(this, &AVentPuzzle::HandleScrewComponentClicked);
	BottomLeftScrew->OnClicked.AddDynamic(this, &AVentPuzzle::HandleScrewComponentClicked);
	BottomRightScrew->OnClicked.AddDynamic(this, &AVentPuzzle::HandleScrewComponentClicked);
}

void AVentPuzzle::HandleScrewComponentClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	AHouseEscapeCharacter* player = Cast<AHouseEscapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Cast<UStaticMeshComponent>(TouchedComponent) && player->GetLastSelectedItem().itemType == ItemType::Screwdriver)
	{
		TouchedComponent->DestroyComponent();
		--screwCount;
	}

	CheckSolution();
}

void AVentPuzzle::InitPuzzleState()
{
	Super::InitPuzzleState();

	TArray<UActorComponent*> components = AInteractable::GetComponentsByTag(UStaticMeshComponent::StaticClass(), "Screw");

	for (UActorComponent* screw : components)
	{
		screw->DestroyComponent();
	}

	Grate->DestroyComponent();
}

void AVentPuzzle::CheckSolution()
{
	if (screwCount == 0)
	{
		FMessage message;
		Grate->DestroyComponent();
		message.itemInfo = Cast<AHouseEscapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetLastSelectedItem();
		messenger->ItemRemoved(message);
		isSolved = true;

		PuzzleCompleted();
	}
}