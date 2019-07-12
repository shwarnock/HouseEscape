// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Interactable.h"
#include "Engine/PointLight.h"
#include "LightSwitch.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API ALightSwitch : public AInteractable
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	APointLight* pointLight;

	UPROPERTY(EditAnywhere)
	APointLight* pointLight2;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnInteract();
	virtual void OnInteract_Implementation() override;

	ALightSwitch();
};
