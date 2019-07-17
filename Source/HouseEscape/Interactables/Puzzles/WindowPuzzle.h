// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactables/Puzzles/Puzzle.h"
#include "Components/TimelineComponent.h"
#include "WindowPuzzle.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API AWindowPuzzle : public APuzzle
{
	enum Windows { LEFT, CENTER, RIGHT };

	GENERATED_BODY()

	AWindowPuzzle();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CenterWindowBottom;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CenterWindowTop;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* LeftWindowBottom;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RightWindowBottom;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* RightWindowTop;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CenterBox;

	UPROPERTY(EditAnywhere)
	UBoxComponent* RightBox;

protected:
	void OnInteract_Implementation() override;

	void HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	void BeginPlay() override;

private:
	Windows CurrentInteraction;

	UPROPERTY()
	UTimelineComponent* Timeline;

	UPROPERTY()
	UCurveFloat* FloatCurve;

	UFUNCTION()
	void TimelineCallback(float val);

	UFUNCTION()
	void TimelineFinishedCallback();

	UPROPERTY()
	TEnumAsByte<ETimelineDirection::Type> TimelineDirection;

	void Tick(float DeltaTime) override;
};
