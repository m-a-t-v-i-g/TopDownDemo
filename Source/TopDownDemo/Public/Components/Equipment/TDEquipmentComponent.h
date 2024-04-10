/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

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

	void InitEquipmentComponent();

	/** Экипировать предмет в любой из доступных слотов. */
	void EquipItem(UTDWeaponObject* WeaponObject);

protected:
	/** Параметры для создания слотов экипировки. */
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TArray<FTDEquipmentSlotParams> Slots;

	/** Действующие экипировочные слоты. */
	UPROPERTY(EditInstanceOnly, Category = "Equipment")
	TArray<UTDEquipmentSlot*> EquipmentSlots;

	TWeakObjectPtr<UTDEquipmentSlot> PrimarySlot;
	TWeakObjectPtr<UTDEquipmentSlot> SecondarySlot;
	TWeakObjectPtr<UTDWeaponComponent> WeaponComponent;
	
	UTDEquipmentSlot* CreateSlot(FTDEquipmentSlotParams SlotParams);
	
	void BindSlot(UTDEquipmentSlot* SlotToBind);
	
public:
	/** Проверить, есть ли доступный слот для добавления предмета в него. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Equipment")
	bool IsAnySlotAvailableFor(const UTDWeaponObject* WeaponObject);

	/** Получить слот по типу. */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Equipment")
	UTDEquipmentSlot* GetSlotByType(ETDEquipmentType EquipmentType);

private:
	UFUNCTION()
	void OnPrimarySlotChanged(UTDWeaponObject* WeaponObject, bool bEquipped);

	UFUNCTION()
	void OnSecondarySlotChanged(UTDWeaponObject* WeaponObject, bool bEquipped);

	UPROPERTY(EditInstanceOnly, Category = "Equipment")
	TMap<UTDEquipmentSlot*, UTDWeaponObject*> EquippedItems;
};
