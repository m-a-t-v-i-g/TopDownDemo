﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment/TDEquipmentSlot.h"
#include "Equipment/TDEquipmentComponent.h"

UTDEquipmentSlot::UTDEquipmentSlot()
{
	Equipment = GetTypedOuter<UTDEquipmentComponent>();
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

void UTDEquipmentSlot::InitSlot(FTDEquipmentSlotParams SlotParams)
{
	SlotName = SlotParams.SlotName;
	SlotType = SlotParams.SlotType;
}

void UTDEquipmentSlot::EquipSlot(UTDWeaponObject* NewItemObject)
{
	ItemObject = NewItemObject;
	bEquipped = true;
	OnSlotChangedDelegate.Broadcast(ItemObject, bEquipped);
}

void UTDEquipmentSlot::UnequipSlot(UTDWeaponObject* OldItemObject)
{
	ItemObject = nullptr;
	bEquipped = false;
	OnSlotChangedDelegate.Broadcast(ItemObject, bEquipped);
}