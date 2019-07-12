// Fill out your copyright notice in the Description page of Project Settings.

#include "Key.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ADoorKey::ADoorKey()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> KeyMesh(TEXT("/Game/StaticMeshes/Items/Key/key.key"));
	StaticMeshComponent->SetStaticMesh(KeyMesh.Object);

	AInteractable::SetActorEnableCollision(false);
	RootComponent->ToggleVisibility(false);
	RootComponent->SetRelativeScale3D(FVector(0.15f, 0.15f, 0.15f));
	
	BoxComponent->SetRelativeScale3D(FVector(10.0f, 9.75f, 9.5f));

	interactType = Interacts::Key;
}

// Called when the game starts or when spawned
void ADoorKey::BeginPlay()
{
	AInteractable::BeginPlay();
	
}

// Called every frame
void ADoorKey::Tick(float DeltaTime)
{
	AInteractable::Tick(DeltaTime);

}

void ADoorKey::OnInteract_Implementation()
{
	FMessage message;
	message.room = room;
	messenger->KeyPickedUp(message);
	saveGameUtil->AddKey(room);
	Destroy();
}