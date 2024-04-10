/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

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
