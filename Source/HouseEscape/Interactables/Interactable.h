// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Messenger.h"
#include "SaveGameUtil.h"
#include "Enums.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialInterface.h"
#include "GameFramework/Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

#include "InteractInterface.h"
#include "Interactable.generated.h"

class AHouseEscapeCharacter;

UCLASS()
class HOUSEESCAPE_API AInteractable : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxComponent;

	UMessenger* messenger;

	USaveGameUtil* saveGameUtil;

	virtual void OnInteract_Implementation() override;
	virtual void OnUseItem_Implementation(FMessage message) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<Interacts> interactType;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Of the valid list of interactable targets, find the one closest to center of camera
	static AInteractable* FindMostDesirableTarget(TArray<AInteractable*> interactables, AHouseEscapeCharacter* player);

	void SetRenderDepth(bool setRender);

	TEnumAsByte<Interacts> GetInteractType();

protected:

	UFUNCTION()
	virtual void HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool IsPlayerOverlapping();

	UStaticMeshComponent* meshToRender;

	FGuid uniqueId;

	bool IsValidInteract;
};
