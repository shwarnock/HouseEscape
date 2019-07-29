// Fill out your copyright notice in the Description page of Project Settings.

#include "ComboPuzzleComp.h"
#include "UObject/ConstructorHelpers.h"
#include "HouseEscapeGameInstance.h"
#include "MessageStruct.h"

int UComboPuzzleComp::num;

void UComboPuzzleComp::SetPuzzleIndex(int index)
{
	puzzleIndex = index;
}

int UComboPuzzleComp::GetPuzzleIndex() const
{
	return puzzleIndex;
}

UComboPuzzleComp::UComboPuzzleComp()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> RedMat(TEXT("/Game/Materials/WirePuzzle/Red.Red"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GreenMat(TEXT("/Game/Materials/WirePuzzle/Green.Green"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> WhiteMat(TEXT("/Game/Materials/WirePuzzle/Unselected.Unselected"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> GreyMat(TEXT("/Game/Materials/WirePuzzle/Selected.Selected"));

	GreenMaterial = GreenMat.Object;
	RedMaterial = RedMat.Object;
	UnSelectedMaterial = GreyMat.Object;
	SelectedMaterial = WhiteMat.Object;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	++num;
	FString number = FString::FromInt(num);
	FString name = FString("Mesh") + number;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(*name));
	if (mesh)
	{
		mesh->SetStaticMesh(StaticMesh.Object);
		mesh->SetRelativeLocation(FVector::ZeroVector);
		mesh->SetupAttachment(this);
		SetPieceMaterial(NotSelected);
	}
	
	name = FString("Box") + number;
	box = CreateDefaultSubobject<UBoxComponent>(FName(*name));
	if (box)
	{
		box->SetupAttachment(this);
		box->SetBoxExtent(FVector(95, 95, 75));
		box->SetRelativeLocation(FVector(0, 30, 25));
		box->OnComponentBeginOverlap.AddDynamic(this, &UComboPuzzleComp::HandleBeginOverlap);
		box->OnComponentEndOverlap.AddDynamic(this, &UComboPuzzleComp::HandleEndOverlap);
	}

	name = FString("Text") + number;
	textRender = CreateDefaultSubobject<UTextRenderComponent>(FName(*name));
	if (textRender)
	{
		textRender->SetupAttachment(this);
		textRender->SetRelativeLocation(FVector(0, 0, 75));
		textRender->SetRelativeRotation(FRotator(0, 90, 0));
		textRender->SetupAttachment(this);
		textRender->SetText(FText());
	}
}

void UComboPuzzleComp::SetText(FText text)
{
	textRender->SetText(text);
}

void UComboPuzzleComp::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FMessage message;
	message.comp = this;
	Cast<UHouseEscapeGameInstance>(GetWorld()->GetGameInstance())->GetMessenger()->OverlapPuzzleComp(message);
}

void UComboPuzzleComp::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	FMessage message;
	message.comp = this;
	Cast<UHouseEscapeGameInstance>(GetWorld()->GetGameInstance())->GetMessenger()->EndOverlapPuzzleComp(message);
}

void UComboPuzzleComp::SetPieceMaterial(PieceStates state)
{
	switch (state)
	{
		case Correct:
			mesh->SetMaterial(0, GreenMaterial);
			break;
		case Incorrect:
			mesh->SetMaterial(0, RedMaterial);
			break;
		case NotSelected:
			mesh->SetMaterial(0, UnSelectedMaterial);
			break;
		case Selected:
			mesh->SetMaterial(0, SelectedMaterial);
			break;
	}
}

void UComboPuzzleComp::ResetNum()
{
	num = 0;
}