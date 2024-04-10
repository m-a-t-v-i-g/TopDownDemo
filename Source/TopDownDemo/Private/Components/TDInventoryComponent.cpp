/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "TDInventoryComponent.h"
#include "Objects/TDItemObject.h"
#include "Objects/TDMedObject.h"

UTDInventoryComponent::UTDInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDInventoryComponent::AddItem(UTDItemObject* ItemObject)
{
	check(!InventoryItems.Contains(ItemObject));

	InventoryItems.Add(ItemObject);
	OnItemAdded.Broadcast(ItemObject);
}

void UTDInventoryComponent::RemoveItem(UTDItemObject* ItemObject)
{
	check(InventoryItems.Contains(ItemObject));

	InventoryItems.Remove(ItemObject);
	OnItemRemoved.Broadcast(ItemObject);
}

UTDItemObject* UTDInventoryComponent::FindItemByAsset(UTDItemAsset* AssetType)
{
	for (auto EachItem : InventoryItems)
	{
		if (EachItem->GetItemAsset() == AssetType)
		{
			return EachItem;
		}
	}
	return nullptr;
}

UTDItemObject* UTDInventoryComponent::FindMedkit()
{
	UTDItemObject* Medkit = nullptr;
	if (InventoryItems.Num() > 0)
	{
		Medkit = *InventoryItems.FindByPredicate([](const UTDItemObject* ItemObject)
	   {
		   return ItemObject->IsA<UTDMedObject>();
	   });
	}
	return Medkit;
}
