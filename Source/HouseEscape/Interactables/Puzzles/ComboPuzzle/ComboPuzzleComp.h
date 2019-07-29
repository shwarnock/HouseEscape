// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "ComboPuzzleComp.generated.h"

/**
 * 
 */
UCLASS()
class HOUSEESCAPE_API UComboPuzzleComp : public USceneComponent
{
	GENERATED_BODY()

	UComboPuzzleComp();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBoxComponent* box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTextRenderComponent* textRender;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* mesh;

	void SetPuzzleIndex(int index);
	int GetPuzzleIndex() const;

	void Init(int index);

	static enum PieceStates { NotSelected, Selected, Correct, Incorrect };

	void SetText(FText text);

	bool operator<(const UComboPuzzleComp& iRhs) const
	{
		return puzzleIndex < iRhs.GetPuzzleIndex();
	}

	void SetPieceMaterial(PieceStates state);

	static void ResetNum();

private:
	int puzzleIndex;

	UFUNCTION()
	virtual void HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UMaterialInterface* GreenMaterial;
	UMaterialInterface* RedMaterial;
	UMaterialInterface* UnSelectedMaterial;
	UMaterialInterface* SelectedMaterial;

	static int num;
};
