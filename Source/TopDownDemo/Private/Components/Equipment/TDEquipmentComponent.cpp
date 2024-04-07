// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment/TDEquipmentComponent.h"

UTDEquipmentComponent::UTDEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDEquipmentComponent::AddEquipmentSlot(UTDEquipmentSlot* Slot)
{
	Modify(false);

	bool bAlreadyInSet = false;
	EquipmentSlots.Add(Slot, &bAlreadyInSet);
}
