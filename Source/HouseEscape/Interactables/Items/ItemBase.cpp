// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"

void AItemBase::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsPlayerOverlapping())
	{
		FMessage message;
		message.interactableType = Interacts::Item;
		messenger->CollideWithInteractable(message);
		StaticMeshComponent->SetRenderCustomDepth(true);
	}
}

void AItemBase::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!IsPlayerOverlapping())
	{
		FMessage message;
		message.interactableType = Interacts::Item;
		messenger->EndCollideWithInteractable(message);
		StaticMeshComponent->SetRenderCustomDepth(false);
	}
}

void AItemBase::OnInteract_Implementation()
{
	FMessage message;
	message.itemInfo = itemInfo;
	messenger->ItemPickedUp(message);
	Destroy();
}