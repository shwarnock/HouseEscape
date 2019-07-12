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

public:
	void CollideWithInteractable(FMessage message);
	void EndCollideWithInteractable(FMessage message);

	void PuzzleSolved(FMessage message);
	void RemoveAllWidgets();

	void KeyPickedUp(FMessage message);

	void ItemPickedUp(FMessage message);

	void AddInteractTarget(FMessage message);
	void RemoveInteractTarget(FMessage message);

	void UpdateInteractUI(FMessage message);
};
