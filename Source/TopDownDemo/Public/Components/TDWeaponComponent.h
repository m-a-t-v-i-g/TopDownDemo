/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment/TDEquipmentComponent.h"
#include "TDWeaponComponent.generated.h"

class ATDCharacter;
class ATDWeaponActor;

USTRUCT(BlueprintType)
struct FTDWeaponSlot
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Slot")
	FName SocketName;
	
	UPROPERTY(EditAnywhere, Category = "Slot")
	TWeakObjectPtr<ATDWeaponActor> WeaponActor;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup = "TopDownDemo")
class TOPDOWNDEMO_API UTDWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDWeaponComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void InitWeaponComponent(ATDCharacter* Character);

#pragma region Handed
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<ATDWeaponActor> HandedWeapon;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	FName HandAttachPoint;

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UpdateHandedWeapon(int SlotIndex);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void MoveHandedWeaponToBelt(FName& MovingSlot);

	void StartShot();
	void StopShot();
	void StartReload();

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FHitResult ShotLocation;

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool bIsShooting = false;

#pragma endregion Handed

#pragma region Belt

protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TMap<FName, FTDWeaponSlot> BeltMap;

public:
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void UpdateBeltWeapon(FName SlotName, UTDWeaponObject* WeaponObject);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	ATDWeaponActor* SpawnWeaponOnBelt(FName SlotName, UTDWeaponObject* FromObject);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	bool HasHandedWeapon();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	bool HasBeltWeapon(FName SlotName);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	int GetAmmoInWeapon();

#pragma endregion Belt

private:
	TWeakObjectPtr<class UTDInventoryComponent> Inventory;
};
