// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HouseEscapeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Components/SkeletalMeshComponent.h"
#include "HouseEscapeGameInstance.h"
#include "Enums.h"
#include "Door.h"
#include "Kismet/GameplayStatics.h"
#include "InteractInterface.h"

#include "DrawDebugHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

AHouseEscapeCharacter::AHouseEscapeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	StaticMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	StaticMesh->SetOnlyOwnerSee(true);
	StaticMesh->SetupAttachment(FirstPersonCameraComponent);
	StaticMesh->bCastDynamicShadow = false;
	StaticMesh->CastShadow = false;
	StaticMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	StaticMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	isOverlapping = false;
	mostDesirableTarget = nullptr;
}

void AHouseEscapeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	StaticMesh->SetHiddenInGame(false, true);

	messenger = Cast<UHouseEscapeGameInstance>(GetWorld()->GetGameInstance())->GetMessenger();
	messenger->OnItemPickedUp.AddDynamic(this, &AHouseEscapeCharacter::HandleItemPickedUp);
	messenger->OnAddInteractTarget.AddDynamic(this, &AHouseEscapeCharacter::AddInteractTarget);
	messenger->OnRemoveInteract.AddDynamic(this, &AHouseEscapeCharacter::RemoveInteractTarget);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AHouseEscapeCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind fire event
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AHouseEscapeCharacter::OnInteract);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AHouseEscapeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AHouseEscapeCharacter::MoveRight);

	//Bind Camera movement
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AHouseEscapeCharacter::OnInteract()
{
	if (currentTargets.Num() == 0)
	{
		return;
	}

	if (currentTargets.Num() == 1)
	{
		IInteractInterface::Execute_OnInteract(currentTargets[0]);
		return;
	}

	IInteractInterface::Execute_OnInteract(AInteractable::FindMostDesirableTarget(currentTargets, this));
}

void AHouseEscapeCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AHouseEscapeCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AHouseEscapeCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AHouseEscapeCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AHouseEscapeCharacter::HandleItemPickedUp(FMessage message)
{
	items.Add(message.itemInfo);
}

void AHouseEscapeCharacter::AddInteractTarget(FMessage message)
{
	currentTargets.Add(message.interact);
	isOverlapping = true;
	AInteractable* tempTarget = AInteractable::FindMostDesirableTarget(currentTargets, this);

	if (mostDesirableTarget == nullptr)
	{
		mostDesirableTarget = tempTarget;
		mostDesirableTarget->SetRenderDepth(true);
		messenger->CollideWithInteractable(message);
	} 
	else if (mostDesirableTarget != tempTarget)
	{
		mostDesirableTarget->SetRenderDepth(false);
		mostDesirableTarget = tempTarget;
		mostDesirableTarget->SetRenderDepth(true); 
		messenger->CollideWithInteractable(message);
	}
}

void AHouseEscapeCharacter::RemoveInteractTarget(FMessage message)
{
	currentTargets.Remove(message.interact);
	mostDesirableTarget->SetRenderDepth(false);
	if (currentTargets.Num() == 0)
	{
		isOverlapping = false;
		mostDesirableTarget = nullptr;
		messenger->EndCollideWithInteractable(message);
	}
	else
	{
		mostDesirableTarget = AInteractable::FindMostDesirableTarget(currentTargets, this);
		mostDesirableTarget->SetRenderDepth(true);
		messenger->CollideWithInteractable(message);
	}
}

bool AHouseEscapeCharacter::AnyCurrentTargets()
{
	return currentTargets.Num() > 0;
}

TArray<AInteractable*> AHouseEscapeCharacter::GetCurrentTargets()
{
	return currentTargets;
}

void AHouseEscapeCharacter::Tick(float DeltaSeconds)
{
	if (FirstPersonCameraComponent->GetForwardVector() != CameraForward && AnyCurrentTargets())
	{
		AInteractable* tempMostDesirable = AInteractable::FindMostDesirableTarget(currentTargets, this);
		if (mostDesirableTarget != tempMostDesirable)
		{
			CameraForward = FirstPersonCameraComponent->GetForwardVector();
			mostDesirableTarget->SetRenderDepth(false);
			mostDesirableTarget = tempMostDesirable;
			mostDesirableTarget->SetRenderDepth(true);
			FMessage message;
			message.interactableType = mostDesirableTarget->GetInteractType();
			if (Cast<ADoor>(mostDesirableTarget))
			{
				message.doorState = Cast<ADoor>(mostDesirableTarget)->GetDoorState();
			}
			messenger->CollideWithInteractable(message);
		}
	}
}
