/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDInteractionInterface.generated.h"

UINTERFACE()
class UTDInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class TOPDOWNDEMO_API ITDInteractionInterface
{
	GENERATED_BODY()

public:
	bool bIsInteractable = true;

	virtual void OnInteraction(AActor* Interactor);
};
