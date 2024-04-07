// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDEquipmentComponent.h"
#include "UObject/Object.h"
#include "TDEquipmentSlot.generated.h"

class UTDWeaponObject;

UCLASS()
class TOPDOWNDEMO_API UTDEquipmentSlot : public UObject
{
	GENERATED_BODY()

public:
	UTDEquipmentSlot();
	
	virtual void PostInitProperties() override;

	void EquipSlot(UTDWeaponObject* NewItemObject);
	void UnequipSlot(UTDWeaponObject* OldItemObject);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slot")
	FName SlotName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slot")
	ETDEquipmentType SlotType;

private:
	TObjectPtr<UTDEquipmentComponent> Equipment;

	TObjectPtr<UTDWeaponObject> ItemObject;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Slot")
	bool bEquipped = false;
};
