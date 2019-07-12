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

ALightSwitch::ALightSwitch()
{
	interactType = Interacts::LightSwitch;
}