// Fill out your copyright notice in the Description page of Project Settings.e
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Delegates/Delegate.h"
#include "MessageStruct.h"
#include "Messenger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCollideWithInteractableDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndCollideWithInteractDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPuzzleSolvedDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FKeyPickedUpDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemPickedUpDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddInteractDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemoveInteractDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateInteractUIDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FToggleInventoryDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemSelected, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemRemovedDelegate, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOverlapComboPuzzleComp, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndOverlapComboPuzzleComp, FMessage, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRemoveAllWidgetsDelegate);

UCLASS(BlueprintType)
class UMessenger : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCollideWithInteractableDelegate OnCollideWithInteractable;

	UPROPERTY(BlueprintAssignable)
	FEndCollideWithInteractDelegate OnEndCollideWithInteractable;

	UPROPERTY(BlueprintAssignable)
	FRemoveAllWidgetsDelegate OnRemoveAllWidgets;

	UPROPERTY(BlueprintAssignable)
	FPuzzleSolvedDelegate OnPuzzleSolved;

	UPROPERTY()
	FKeyPickedUpDelegate OnKeyPickedUp;

	UPROPERTY()
	FItemPickedUpDelegate OnItemPickedUp;

	UPROPERTY()
	FAddInteractDelegate OnAddInteractTarget;

	UPROPERTY()
	FRemoveInteractDelegate OnRemoveInteract;

	UPROPERTY(BlueprintAssignable)
	FUpdateInteractUIDelegate OnUpdateInteractUI;

	UPROPERTY(BlueprintAssignable)
	FToggleInventoryDelegate OnToggleInventory;

	UPROPERTY()
	FInventoryItemSelected OnInventoryItemSelected;

	UPROPERTY()
	FItemRemovedDelegate OnItemRemoved;

	UPROPERTY()
	FOverlapComboPuzzleComp OnOverlapPuzzleComp;

	UPROPERTY()
	FEndOverlapComboPuzzleComp OnEndOverlapPuzzleComp;

public:
	void CollideWithInteractable(FMessage message);
	void EndCollideWithInteractable(FMessage message);

	void PuzzleSolved(FMessage message);

	UFUNCTION(BlueprintCallable)
	void RemoveAllWidgets();

	void KeyPickedUp(FMessage message);

	void ItemPickedUp(FMessage message);

	UFUNCTION(BlueprintCallable)
	void AddInteractTarget(FMessage message);

	UFUNCTION(BlueprintCallable)
	void RemoveInteractTarget(FMessage message);

	void UpdateInteractUI(FMessage message);

	void ToggleInventory(FMessage message);

	UFUNCTION(BlueprintCallable)
	void InventoryItemSelected(FMessage message);

	void ItemRemoved(FMessage message);

	void OverlapPuzzleComp(FMessage message);

	void EndOverlapPuzzleComp(FMessage message);
};
