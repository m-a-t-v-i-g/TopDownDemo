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
	if (UTDEquipmentComponent* FindEquipment = Interactor->FindComponentByClass<UTDEquipmentComponent>())
	{
		UTDWeaponObject* WeaponObject = Cast<UTDWeaponObject>(CreateItemObject(UTDWeaponObject::StaticClass()));
		check(WeaponObject);
	}
	else if (UTDInventoryComponent* FindInventory = Interactor->FindComponentByClass<UTDInventoryComponent>())
	{
		UTDWeaponObject* WeaponObject = Cast<UTDWeaponObject>(CreateItemObject(UTDWeaponObject::StaticClass()));
		check(WeaponObject);
		
		FindInventory->AddItem(WeaponObject);
	}
	Destroy();
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
