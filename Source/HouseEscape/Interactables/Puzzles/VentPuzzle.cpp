// Fill out your copyright notice in the Description page of Project Settings.

#include "VentPuzzle.h"
#include "HouseEscapeCharacter.h"

AVentPuzzle::AVentPuzzle()
{
	//Create ScrewHeads
	TopLeftScrew = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopLeftScrew"));
	TopRightScrew = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopRightScrew"));
	BottomLeftScrew = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomLeftScrew"));
	BottomRightScrew = AInteractable::CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomRightScrew"));

	TArray<UStaticMeshComponent*> components;
	AInteractable::GetComponents<UStaticMeshComponent>(components);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Screw(TEXT("/Game/StaticMeshes/Items/ScrewHead.ScrewHead"));
	//Setup Components
	int componentCount = components.Num();
	for (int i = 0; i < componentCount; ++i)
	{
		UStaticMeshComponent* component = components[i];
		if (component == RootComponent)
		{
			continue;
		}

		component->SetStaticMesh(Screw.Object);
		component->SetWorldScale3D(FVector(0.15f, 0.15f, 0.15f));
		component->SetupAttachment(RootComponent);
		component->OnClicked.AddDynamic(this, &AVentPuzzle::HandleComponentClicked);
	}

	puzzleType = Puzzles::VentPuzzle;

	screwCount;
}

void AVentPuzzle::HandleComponentClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	AHouseEscapeCharacter* player = Cast<AHouseEscapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Cast<UStaticMeshComponent>(TouchedComponent) && player->GetLastSelectedItem().itemType == ItemType::Screwdriver)
	{
		TouchedComponent->DestroyComponent();
	}

	if (screwCount == 0)
	{
		FMessage message;
		message.room = roomPuzzleUnlocks;
		messenger->PuzzleSolved(message);
	}
}

void AVentPuzzle::InitPuzzleState()
{
	Super::InitPuzzleState();

	TArray<UStaticMeshComponent*> components;
	AInteractable::GetComponents<UStaticMeshComponent>(components);

	for (UStaticMeshComponent* screw : components)
	{
		screw->DestroyComponent();
	}
}