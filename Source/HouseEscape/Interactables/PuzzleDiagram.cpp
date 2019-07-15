// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzleDiagram.h"

APuzzleDiagram::APuzzleDiagram()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Plane(TEXT("/Engine/BasicShapes/Plane.Plane"));

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DiagramMat(TEXT("/Game/Materials/PuzzleDiagram.PuzzleDiagram"));
	UMaterialInterface* DiagramMaterial = (UMaterialInterface*)DiagramMat.Object;

	StaticMeshComponent->SetStaticMesh(Plane.Object);
	StaticMeshComponent->SetMaterial(0, DiagramMaterial);

	BoxComponent->SetBoxExtent(FVector(80, 80, 32));
	BoxComponent->SetRelativeLocation(FVector(0, 0, 40));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetRelativeLocation(FVector(0, 0, 120));
	CameraComponent->SetWorldRotation(FRotator(-90, 0, -90));
	CameraComponent->SetupAttachment(AInteractable::RootComponent);

	interactType = Interacts::Generic;
}

void APuzzleDiagram::OnInteract_Implementation()
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
		message.interactableType = interactType;
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