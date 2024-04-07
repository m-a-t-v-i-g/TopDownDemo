// Fill out your copyright notice in the Description page of Project Settings.

#include "TDWeaponActor.h"
#include "TDInventoryComponent.h"
#include "Equipment/TDEquipmentComponent.h"
#include "Objects/TDWeaponObject.h"

ATDWeaponActor::ATDWeaponActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATDWeaponActor::OnInteraction(AActor* Interactor)
{
	UTDWeaponObject* WeaponObject = Cast<UTDWeaponObject>(CreateItemObject(UTDWeaponObject::StaticClass()));
	check(WeaponObject);

	if (UTDEquipmentComponent* FindEquipment = Interactor->FindComponentByClass<UTDEquipmentComponent>())
	{
		if (FindEquipment->IsAnySlotAvailable(WeaponObject))
		{
			FindEquipment->EquipItem(WeaponObject);
			Destroy();
			return;
		}
	}
	
	if (UTDInventoryComponent* FindInventory = Interactor->FindComponentByClass<UTDInventoryComponent>())
	{
		FindInventory->AddItem(WeaponObject);
		Destroy();
		return;
	}

	WeaponObject->MarkAsGarbage();
}

UTDItemObject* ATDWeaponActor::CreateItemObject(UClass* WeaponObjectClass)
{
	UTDWeaponObject* CreatedWeaponObject = nullptr;
	if (WeaponObjectClass->IsChildOf<UTDWeaponObject>())
	{
		CreatedWeaponObject = Cast<UTDWeaponObject>(Super::CreateItemObject(WeaponObjectClass));
		*CreatedWeaponObject = this;
	}
	return CreatedWeaponObject;
}
