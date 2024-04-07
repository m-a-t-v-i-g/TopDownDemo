// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment/TDEquipmentSlot.h"
#include "Equipment/TDEquipmentComponent.h"

UTDEquipmentSlot::UTDEquipmentSlot()
{
	SlotType = ETDEquipmentType::None;
}

void UTDEquipmentSlot::PostInitProperties()
{
	UObject::PostInitProperties();
	
	if (Equipment)
	{
		Equipment->AddEquipmentSlot(this);
	}
}

void UTDEquipmentSlot::EquipSlot(UTDWeaponObject* NewItemObject)
{
	ItemObject = NewItemObject;
	bEquipped = true;
}

void UTDEquipmentSlot::UnequipSlot(UTDWeaponObject* OldItemObject)
{
	ItemObject = nullptr;
	bEquipped = false;
}
