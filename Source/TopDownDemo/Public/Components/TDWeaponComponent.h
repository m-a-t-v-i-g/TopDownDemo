// Fill out your copyright notice in the Description page of Project Settings.

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

	FHitResult ShotLocation;
	
	bool bIsShooting = false;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TMap<FName, FTDWeaponSlot> BeltMap;

public:
	void UpdateBeltWeapon(FName SlotName, UTDWeaponObject* WeaponObject);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	ATDWeaponActor* SpawnWeaponOnBelt(FName SlotName, UTDWeaponObject* FromObject);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	bool HasHandedWeapon();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	bool HasBeltWeapon(FName SlotName);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	int GetAmmoInWeapon();

private:
	TWeakObjectPtr<class UTDInventoryComponent> Inventory;
};
