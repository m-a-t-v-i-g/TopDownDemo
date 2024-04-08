// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDEquipmentComponent.generated.h"

class UTDWeaponComponent;
class UTDWeaponObject;

UENUM(BlueprintType)
enum class ETDEquipmentType : uint8
{
	None,
	Primary,
	Secondary
};

USTRUCT(BlueprintType)
struct FTDEquipmentSlotParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Slot")
	FName SlotName;
	
	UPROPERTY(EditAnywhere, Category = "Slot")
	ETDEquipmentType SlotType;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup = "TopDownDemo")
class TOPDOWNDEMO_API UTDEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDEquipmentComponent();

	void AddEquipmentSlot(class UTDEquipmentSlot* Slot);

	void InitEquipment();

	void EquipItem(UTDWeaponObject* WeaponObject);
	void UnequipItem(UTDWeaponObject* WeaponObject);

	bool IsAnySlotAvailable(const UTDWeaponObject* WeaponObject);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TArray<FTDEquipmentSlotParams> Slots;
	
	TWeakObjectPtr<UTDEquipmentSlot> PrimarySlot;
	TWeakObjectPtr<UTDEquipmentSlot> SecondarySlot;

	TWeakObjectPtr<UTDWeaponComponent> WeaponComponent;
	
	UTDEquipmentSlot* CreateSlot(FTDEquipmentSlotParams SlotParams);
	
	void BindSlot(UTDEquipmentSlot* SlotToBind);
	
private:
	UPROPERTY(EditInstanceOnly, Category = "Equipment")
	TMap<UTDEquipmentSlot*, UTDWeaponObject*> EquippedItems;
	
	UPROPERTY(EditInstanceOnly, Category = "Equipment")
	TArray<UTDEquipmentSlot*> EquipmentSlots;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Equipment")
	UTDEquipmentSlot* GetSlotByType(ETDEquipmentType EquipmentType);

private:
	UFUNCTION()
	void OnPrimarySlotChanged(UTDWeaponObject* WeaponObject, bool bEquipped);

	UFUNCTION()
	void OnSecondarySlotChanged(UTDWeaponObject* WeaponObject, bool bEquipped);
};
