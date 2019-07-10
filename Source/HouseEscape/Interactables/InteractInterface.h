#pragma once

#include "Interface.h"
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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
	void OnInteract();
};