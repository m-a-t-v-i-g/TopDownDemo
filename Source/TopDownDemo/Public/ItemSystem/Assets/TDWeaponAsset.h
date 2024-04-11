/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "TDItemAsset.h"
#include "Equipment/TDEquipmentComponent.h"
#include "TDWeaponAsset.generated.h"

class UTDAmmoAsset;

UCLASS()
class TOPDOWNDEMO_API UTDWeaponAsset : public UTDItemAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	ETDEquipmentType EquipmentType = ETDEquipmentType::None;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = "0", ForceUnits = "pc"))
	int MaxRounds = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = "0", ForceUnits = "s"))
	float ReloadTime = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = "0", ForceUnits = "rpm"))
	int FireRate = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = "0"))
	float BaseDamage = 0.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	bool bAutomatic = false;
	
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TObjectPtr<UTDAmmoAsset> AmmoType;
};
