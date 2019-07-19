// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Interactable.h"
#include "Components/TimelineComponent.h"
#include "Door.generated.h"

UCLASS()
class HOUSEESCAPE_API ADoor : public AInteractable
{
	GENERATED_BODY()

	ADoor();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorComponent;
	
protected:

	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnInteract();
	void OnInteract_Implementation() override;

	void BeginPlay() override;

	void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<DoorStates> doorState;

private:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<Rooms> neededKey;

	UFUNCTION()
	void HandleKeyPickedUp(FMessage message);

	UPROPERTY()
	UTimelineComponent* MyTimeline;

	UPROPERTY()
	UCurveFloat* FloatCurve;

	UFUNCTION()
	void TimelineCallback(float val);

	UFUNCTION()
	void TimelineFinishedCallback();

	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	UFUNCTION()
	void CloseDoor();

	FTimerHandle UnusedHandle;
	FTimerDelegate TimerDel;

public:
	TEnumAsByte<DoorStates> GetDoorState();
};
