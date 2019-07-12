// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemBase.h"
#include "HouseEscapeCharacter.h"

void AItemBase::OnInteract_Implementation()
{
	FMessage message;
	message.itemInfo = itemInfo;
	messenger->ItemPickedUp(message);
	Destroy();
}

AItemBase::AItemBase()
{
	interactType = Interacts::Item;
}