// Fill out your copyright notice in the Description page of Project Settings.

#include "TDInventoryComponent.h"

UTDInventoryComponent::UTDInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDInventoryComponent::AddItem(UTDItemObject* ItemObject)
{
	check(!InventoryItems.Contains(ItemObject));

	InventoryItems.Add(ItemObject);
	OnInventoryChangedDelegate.Broadcast(ItemObject);
}
