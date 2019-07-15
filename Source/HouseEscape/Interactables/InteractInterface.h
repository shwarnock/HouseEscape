#pragma once

#include "Interface.h"
#include "MessageStruct.h"
#include "InteractInterface.generated.h"

UINTERFACE(Blueprintable)
class UInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class IInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void OnInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Item")
	void OnUseItem(FMessage message);
};