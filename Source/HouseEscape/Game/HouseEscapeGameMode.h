// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Messenger.h"
#include "GameFramework/GameModeBase.h"
#include "HouseEscapeGameMode.generated.h"

UCLASS(MinimalAPI)
class AHouseEscapeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AHouseEscapeGameMode();

protected:
	virtual void PostInitializeComponents() override;
};



