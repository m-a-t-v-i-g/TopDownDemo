// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Equipment/TDEquipmentComponent.h"
#include "TDWeaponComponent.generated.h"

class ATDWeaponActor;

USTRUCT(BlueprintType)
struct FTDWeaponSlot
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Slot")
	TWeakObjectPtr<ATDWeaponActor> WeaponActor;

	UPROPERTY(EditAnywhere, Category = "Slot")
	TWeakObjectPtr<UTDWeaponObject> WeaponObject;

	UPROPERTY(EditAnywhere, Category = "Slot")
	ETDEquipmentType SlotType;
};

UCLASS(Blueprintable, BlueprintType, ClassGroup = "TopDownDemo")
class TOPDOWNDEMO_API UTDWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDWeaponComponent();
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<ATDWeaponActor> HandedWeapon;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	TMap<FName, FTDWeaponSlot> BeltMap;
	
	void UpdateBeltWeapon(FName SlotName, UTDWeaponObject* WeaponObject);
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	ATDWeaponActor* SpawnWeaponOnBelt(UTDWeaponObject* FromObject);
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	bool HasBeltWeapon(FName SlotName);
};
