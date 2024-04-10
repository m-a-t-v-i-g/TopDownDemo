/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "TDEquipmentComponent.h"
#include "UObject/Object.h"
#include "TDEquipmentSlot.generated.h"

class UTDWeaponObject;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnSlotChangedDelegate, UTDWeaponObject*, bool)

UCLASS()
class TOPDOWNDEMO_API UTDEquipmentSlot : public UObject
{
	GENERATED_BODY()

public:
	UTDEquipmentSlot();
	
	virtual void PostInitProperties() override;

	void InitSlot(FTDEquipmentSlotParams SlotParams);

	void EquipSlot(UTDWeaponObject* NewItemObject);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slot")
	FName SlotName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slot")
	ETDEquipmentType SlotType;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Slot")
	FORCEINLINE FName GetSlotName() const { return SlotName; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Slot")
	FORCEINLINE ETDEquipmentType GetSlotType() const { return SlotType; }
	
private:
	TObjectPtr<UTDEquipmentComponent> Equipment;
	TObjectPtr<UTDWeaponObject> ItemObject;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slot")
	bool bEquipped = false;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Slot")
	FORCEINLINE UTDWeaponObject* GetWeaponObject() const { return ItemObject; }
	
	FOnSlotChangedDelegate OnSlotChangedDelegate;
};
