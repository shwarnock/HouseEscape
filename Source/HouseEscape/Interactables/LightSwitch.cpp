// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitch.h"
#include "Components/PointLightComponent.h"

void ALightSwitch::OnInteract_Implementation()
{
	if (pointLight->GetLightComponent()->IsActive())
	{
		pointLight->GetLightComponent()->SetActive(false);
		pointLight->GetLightComponent()->ToggleVisibility(false);
	}
	else
	{

		pointLight->GetLightComponent()->SetActive(true);
		pointLight->GetLightComponent()->ToggleVisibility(true);
	}

	if (pointLight2 != nullptr)
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

void ALightSwitch::HandleBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsPlayerOverlapping())
	{
		return;
	}

	FMessage message;
	message.interactableType = Interacts::LightSwitch;
	messenger->CollideWithInteractable(message);
	StaticMeshComponent->SetRenderCustomDepth(true);
}

void ALightSwitch::HandleEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IsPlayerOverlapping())
	{
		return;
	}

	FMessage message;
	message.interactableType = Interacts::LightSwitch;
	messenger->EndCollideWithInteractable(message);
	StaticMeshComponent->SetRenderCustomDepth(false);
}