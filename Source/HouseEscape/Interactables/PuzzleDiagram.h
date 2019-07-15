// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Interactable.h"
#include "Camera/CameraComponent.h"
#include "PuzzleDiagram.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API APuzzleDiagram : public AInteractable
{
	GENERATED_BODY()

	APuzzleDiagram();

	UPROPERTY(EditAnywhere)
	UCameraComponent* CameraComponent;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnInteract();
	void OnInteract_Implementation() override;
};
