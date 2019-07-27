// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitch.h"
#include "Components/PointLightComponent.h"

void ALightSwitch::OnInteract_Implementation()
{
	if (pointLight->GetLightComponent()->IsActive())
	{
		pointLight->GetLightComponent()->SetActive(false);
		pointLight->GetLightComponent()->ToggleVisibility(false);
		SwitchFlip->SetRelativeRotation(FRotator::ZeroRotator);
	}
	else
	{
		pointLight->GetLightComponent()->SetActive(true);
		pointLight->GetLightComponent()->ToggleVisibility(true);
		SwitchFlip->SetRelativeRotation(FRotator(0, 0, -45));
	}

	if (pointLight2 == nullptr)
	{
		return;
	}

	if (pointLight2->GetLightComponent()->IsActive())
	{
		pointLight2->GetLightComponent()->SetActive(false);
		pointLight2->GetLightComponent()->ToggleVisibility(false);
	}
	else
	{

		pointLight2->GetLightComponent()->SetActive(true);
		pointLight2->GetLightComponent()->ToggleVisibility(true);
	}
}

ALightSwitch::ALightSwitch()
{
	interactType = Interacts::LightSwitch;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LightSwitchBase(TEXT("/Game/StaticMeshes/Items/LightSwitch/LightSwitchBase.LightSwitchBase"));
	StaticMeshComponent->SetStaticMesh(LightSwitchBase.Object);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LightSwitchFlip(TEXT("/Game/StaticMeshes/Items/LightSwitch/LightSwitchFlip.LightSwitchFlip"));
	SwitchFlip = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flipper"));
	SwitchFlip->SetStaticMesh(LightSwitchFlip.Object);
	SwitchFlip->SetRelativeLocation(FVector(0, -1, 0));
	SwitchFlip->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LightSwitchScrewTop(TEXT("/Game/StaticMeshes/Items/LightSwitch/LightSwitchScrewTop.LightSwitchScrewTop"));
	TopScrew = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TopScrew"));
	TopScrew->SetStaticMesh(LightSwitchScrewTop.Object);
	TopScrew->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> LightSwitchScrewBottom(TEXT("/Game/StaticMeshes/Items/LightSwitch/LightSwitchScrewBottom.LightSwitchScrewBottom"));
	BottomScrew = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BottomScrew"));
	BottomScrew->SetStaticMesh(LightSwitchScrewBottom.Object);
	BottomScrew->SetupAttachment(RootComponent);

	BoxComponent->SetRelativeLocation(FVector(0, 30, 0));
}