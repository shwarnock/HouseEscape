// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleBoardPieceComponent.h"
#include "HouseEscapeCharacter.h"
#include "Messenger.h"
#include "UObject/ConstructorHelpers.h"
#include "HouseEscapeGameInstance.h"
#include "ItemStruct.h"

int UPuzzleBoardPieceComponent::index = 0;

// Sets default values for this component's properties
UPuzzleBoardPieceComponent::UPuzzleBoardPieceComponent()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> HoverMat(TEXT("/Game/Materials/TranslucentBlack.TranslucentBlack"));
	HoverMaterial = HoverMat.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> StaticMat(TEXT("/Game/Materials/TranslucentMaterial.TranslucentMaterial"));
	StaticMaterial = StaticMat.Object;

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> SlottedMat(TEXT("/Game/Materials/Black.Black"));
	SlottedMaterial = SlottedMat.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DefaultMesh(TEXT("/Game/StaticMeshes/TestMeshes/TranslucentCube.TranslucentCube"));

	++index;
	FString name = FString("PuzzlePiece") + FString::FromInt(index);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*name));
	StaticMesh->SetStaticMesh(DefaultMesh.Object);
	StaticMesh->SetupAttachment(this);

	isSlotted = false;
}


// Called when the game starts
void UPuzzleBoardPieceComponent::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnBeginCursorOver.AddDynamic(this, &UPuzzleBoardPieceComponent::HandleMouseOver);
	StaticMesh->OnEndCursorOver.AddDynamic(this, &UPuzzleBoardPieceComponent::HandleEndMouseOver);
	StaticMesh->OnClicked.AddDynamic(this, &UPuzzleBoardPieceComponent::HandleClicked);
}

void UPuzzleBoardPieceComponent::HandleMouseOver(UPrimitiveComponent* TouchedComponent)
{
	if (!isSlotted) 
	{
		StaticMesh->SetMaterial(0, HoverMaterial);
	}
}

void UPuzzleBoardPieceComponent::HandleEndMouseOver(UPrimitiveComponent* TouchedComponent)
{
	if (!isSlotted)
	{
		StaticMesh->SetMaterial(0, StaticMaterial);
	}
}

void UPuzzleBoardPieceComponent::HandleClicked(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	if (isSlotted)
	{
		return;
	}

	FItem lastClickedItem = Cast<AHouseEscapeCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetLastSelectedItem();
	if (lastClickedItem.itemType == itemType) 
	{
		StaticMesh->SetMaterial(0, SlottedMaterial);
		
		FMessage message;
		message.itemInfo = lastClickedItem;
		Cast<UHouseEscapeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetMessenger()->ItemRemoved(message);

		isSlotted = true;
		CheckSolution.Broadcast();
	}
}

bool UPuzzleBoardPieceComponent::GetIsSlotted()
{
	return isSlotted;
}

void UPuzzleBoardPieceComponent::ResetIndex()
{
	index = 0;
}