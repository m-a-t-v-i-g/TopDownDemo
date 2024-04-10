/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "TDItemAsset.h"
#include "TDAmmoAsset.generated.h"

UCLASS()
class TOPDOWNDEMO_API UTDAmmoAsset : public UTDItemAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo", meta = (ClampMin = "0", ForceUnits = "pc"))
	int MaxAmmo = 0;
};
