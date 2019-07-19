// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MessageStruct.h"
#include "ItemStruct.h"
#include "SaveGameUtil.h"
#include "Interactable.h"
#include "Messenger.h"
#include "HouseEscapeCharacter.generated.h"

class UInputComponent;

UCLASS(config = Game)
class AHouseEscapeCharacter : public ACharacter
{
	GENERATED_BODY()

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* StaticMesh;

	AHouseEscapeCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return StaticMesh; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	bool AnyCurrentTargets();

	TArray<AInteractable*> GetCurrentTargets();

	FItem GetLastSelectedItem();

protected:
	virtual void BeginPlay();

	void OnInteract();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	UPROPERTY(BlueprintReadOnly)
		AInteractable* mostDesirableTarget;

private:
	const float InteractDistance = 300.0f;

	bool isOverlapping;

	TArray<AInteractable*> currentTargets;

	UFUNCTION()
	void AddInteractTarget(FMessage message);

	UFUNCTION()
	void RemoveInteractTarget(FMessage message);

	FVector CameraForward;

	void Tick(float DeltaSeconds) override;

	UMessenger* messenger;
	USaveGameUtil* saveGameUtil;

	void OnInventory();
	bool IsInventoryOpen;

	FItem lastItemSelected;

	UFUNCTION()
	void SetLastItemSelected(FMessage message);

	UFUNCTION()
	void ClearLastItemSelected(FMessage message);
};

