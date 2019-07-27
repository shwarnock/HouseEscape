
// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable.h"
#include "HouseEscapeGameInstance.h"
#include "Engine.h"
#include "HouseEscapeCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	
	RootComponent = StaticMeshComponent;
	RootComponent->SetRelativeLocation(FVector::ZeroVector);
	
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetRelativeLocation(FVector::ZeroVector);

	uniqueId = FGuid::NewGuid();

	IsValidInteract = true;

	meshToRender = StaticMeshComponent;
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	AActor::BeginPlay();
	
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractable::HandleBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AInteractable::HandleEndOverlap);

	UHouseEscapeGameInstance* gameInstance = Cast<UHouseEscapeGameInstance>(GetWorld()->GetGameInstance());
	messenger = gameInstance->GetMessenger();

	saveGameUtil = gameInstance->GetSaveGameUtil();
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	AActor::Tick(DeltaTime);

}

void AInteractable::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsPlayerOverlapping())
	{
		return;
	}

	FMessage message;
	message.interact = this;
	message.interactableType = interactType;
	messenger->AddInteractTarget(message);
}

void AInteractable::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsPlayerOverlapping())
	{
		return;
	}

	FMessage message;
	message.interact = this;
	message.interactableType = interactType;
	messenger->RemoveInteractTarget(message);
}

void AInteractable::OnInteract_Implementation() 
{
}

void AInteractable::OnUseItem_Implementation(FMessage message)
{
}

bool AInteractable::IsPlayerOverlapping()
{
	TArray<UBoxComponent*> components;
	AInteractable::GetComponents<UBoxComponent>(components);
	for (UBoxComponent* box : components)
	{
		if (box->IsOverlappingActor(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
		{
			return true;
		}
	}

	return false;
}

AInteractable* AInteractable::FindMostDesirableTarget(TArray<AInteractable*> interactables, AHouseEscapeCharacter* player)
{
	FVector playerForward = player->GetActorForwardVector();
	playerForward.Normalize();
	FVector playerLocation = player->GetActorLocation();

	if (interactables.Num() == 1)
	{
		FVector vec = (interactables[0]->meshToRender->GetComponentLocation() - playerLocation);
		vec.Normalize();
		return FVector::DotProduct(playerForward, vec) > 0 ? interactables[0] : nullptr;
	}

	AInteractable* mostDesirable = nullptr;
	FVector firstVec;
	float firstDot = -9;
	int loopCutOff = -1;
	for (int i = 0; i < interactables.Num(); ++i)
	{
		firstVec = (interactables[i]->meshToRender->GetComponentLocation() - playerLocation);
		firstVec.Normalize();
		firstDot = FVector::DotProduct(playerForward, firstVec);
		if (firstDot > 0)
		{
			loopCutOff = i;
			mostDesirable = interactables[i];
			break;
		}
	}

	if (loopCutOff == -1)
	{
		return nullptr;
	}

	int count = interactables.Num();
	for (int i = loopCutOff + 1; i < count; ++i)
	{
		FVector secVec = (interactables[i]->meshToRender->GetComponentLocation() - playerLocation);
		secVec.Normalize();
		float secVecDot = FVector::DotProduct(playerForward, secVec);

		if (secVecDot > firstDot)
		{
			mostDesirable = interactables[i];
			firstDot = secVecDot;
		}
	}

	return mostDesirable;
}

void AInteractable::SetRenderDepth(bool renderSet)
{
	if (this != nullptr && meshToRender->IsValidLowLevel())
	{
		meshToRender->SetRenderCustomDepth(renderSet);
	}
}

TEnumAsByte<Interacts> AInteractable::GetInteractType()
{
	return interactType;
}