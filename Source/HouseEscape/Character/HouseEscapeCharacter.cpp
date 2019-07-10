// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "HouseEscapeCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Components/SkeletalMeshComponent.h"
#include "HouseEscapeGameInstance.h"
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
}

void AHouseEscapeCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	StaticMesh->SetHiddenInGame(false, true);

	UHouseEscapeGameInstance* gameInstance = Cast<UHouseEscapeGameInstance>(GetWorld()->GetGameInstance());
	gameInstance->GetMessenger()->OnItemPickedUp.AddDynamic(this, &AHouseEscapeCharacter::HandleItemPickedUp);
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
	FVector RayCastStart = FirstPersonCameraComponent->GetComponentLocation();
	FRotator CameraRotation = FirstPersonCameraComponent->GetComponentRotation();
	FVector RayCastEnd = RayCastStart + (CameraRotation.Vector() * InteractDistance);

	FCollisionQueryParams RV_TraceParams = FCollisionQueryParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	
	DrawDebugLine(GetWorld(), RayCastStart, RayCastEnd, FColor::Green, false, 1, 0, 1);

	//Re-initialize hit info
	FHitResult RV_Hit(ForceInit);

	if (GetWorld()->LineTraceSingleByChannel(RV_Hit, RayCastStart, RayCastEnd, ECC_Pawn, RV_TraceParams))
	{
		if (RV_Hit.GetActor()->GetClass()->ImplementsInterface(UInteractInterface::StaticClass()))
		{
			IInteractInterface::Execute_OnInteract(RV_Hit.GetActor());
		}
	}

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