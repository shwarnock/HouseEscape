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

void AItemBase::BeginPlay()
{
	Super::BeginPlay();

	if (saveGameUtil->DoesPlayHaveItem(itemInfo))
	{
		Destroy();
	}
}

FItem AItemBase::EmptyItem()
{
	FItem item;
	item.itemIndex = -1;
	item.itemType = ItemType::Empty;
	item.name = FText();
	item.texture = nullptr;
	return item;
}