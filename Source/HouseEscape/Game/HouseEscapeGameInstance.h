// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Messenger.h"
#include "SaveGameUtil.h"
#include "HouseEscapeGameInstance.generated.h"

UCLASS()
class UHouseEscapeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	UMessenger* GetMessenger();

	UFUNCTION(BlueprintCallable)
	USaveGameUtil* GetSaveGameUtil();

	UHouseEscapeGameInstance();

private:

	UPROPERTY()
	UMessenger* messenger;

	UPROPERTY()
	USaveGameUtil* saveGame;
};
