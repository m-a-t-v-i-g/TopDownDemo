/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "Objects/TDItemObject.h"
#include "TDMedObject.generated.h"

class ATDMedActor;

UCLASS()
class TOPDOWNDEMO_API UTDMedObject : public UTDItemObject
{
	GENERATED_BODY()
	
public:
	void operator=(const ATDMedActor* MedActor);

	UFUNCTION()
	float GetHealValue();
};
