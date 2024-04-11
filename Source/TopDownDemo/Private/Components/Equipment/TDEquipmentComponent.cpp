/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "Equipment/TDEquipmentComponent.h"
#include "TDCharacter.h"
#include "TDWeaponActor.h"
#include "TDWeaponComponent.h"
#include "Assets/TDWeaponAsset.h"
#include "Equipment/TDEquipmentSlot.h"
#include "Objects/TDWeaponObject.h"

UTDEquipmentComponent::UTDEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDEquipmentComponent::AddEquipmentSlot(UTDEquipmentSlot* Slot)
{
	Modify(false);
	EquipmentSlots.Add(Slot);
}

void UTDEquipmentComponent::InitEquipmentComponent()
{
	PrimarySlot = CreateSlot(Slots[0]);
	SecondarySlot = CreateSlot(Slots[1]);

	/* По стандарту, блок кода, написанный ниже, должен выноситься в отдельный класс экипировки для взаимодействия с
	 * компонентом оружия и персонажем. */
	auto Character = Cast<ATDCharacter>(GetOwner());
	if (!Character)
	{
		return;
	}
	WeaponComponent = Character->GetComponentByClass<UTDWeaponComponent>();

	AddStartingEquipment();
}

void UTDEquipmentComponent::EquipItem(UTDWeaponObject* WeaponObject)
{
	auto DataAsset = Cast<UTDWeaponAsset>(WeaponObject->GetItemAsset());
	if (!DataAsset)
	{
		return;
	}

	auto FreeSlot = GetSlotByType(DataAsset->EquipmentType);
	if (!FreeSlot || FreeSlot->bEquipped)
	{
		return;
	}
	
	FreeSlot->EquipSlot(WeaponObject);
	EquippedItems.Add(FreeSlot, WeaponObject);
}

void UTDEquipmentComponent::AddStartingEquipment()
{
	if (StartingEquipment.Num() == 0) return;

	for (auto EachItem : StartingEquipment)
	{
		auto WeaponActor = NewObject<ATDWeaponActor>(GetTransientPackage(), EachItem);
		if (!WeaponActor) continue;

		WeaponActor->MakeAmmoFull();

		UTDWeaponObject* WeaponObject = Cast<UTDWeaponObject>(WeaponActor->CreateItemObject(UTDWeaponObject::StaticClass()));
		check(WeaponObject);

		if (IsAnySlotAvailableFor(WeaponObject))
		{
			EquipItem(WeaponObject);
			WeaponActor->Destroy();
		}
		else
		{
			WeaponObject->MarkAsGarbage();
		}
	}
}

bool UTDEquipmentComponent::IsAnySlotAvailableFor(const UTDWeaponObject* WeaponObject)
{
	auto DataAsset = Cast<UTDWeaponAsset>(WeaponObject->GetItemAsset());
	if (!DataAsset)
	{
		return false;
	}
	
	for (auto EachSlot : EquipmentSlots)
	{
		if (EachSlot->GetSlotType() == DataAsset->EquipmentType && !EachSlot->bEquipped)
		{
			return true;
		}
	}
	return false;
}

UTDEquipmentSlot* UTDEquipmentComponent::CreateSlot(FTDEquipmentSlotParams SlotParams)
{
	UTDEquipmentSlot* CreatedSlot = NewObject<UTDEquipmentSlot>(this, UTDEquipmentSlot::StaticClass());
	if (IsValid(CreatedSlot))
	{
		CreatedSlot->InitSlot(SlotParams);
		BindSlot(CreatedSlot);
	}
	return CreatedSlot;
}

void UTDEquipmentComponent::BindSlot(UTDEquipmentSlot* SlotToBind)
{
	/* Бинд слота и функции происходит по имени слота. */
	const FString FunctionName = FString(TEXT("On")) + FString(SlotToBind->GetSlotName().ToString()) + FString(TEXT("SlotChanged"));
	SlotToBind->OnSlotChangedDelegate.AddUFunction(this, FName(*FunctionName));
}

UTDEquipmentSlot* UTDEquipmentComponent::GetSlotByType(ETDEquipmentType EquipmentType)
{
	auto Slot = EquipmentSlots.FindByPredicate([EquipmentType](UTDEquipmentSlot* FindSlot)
	{
		return FindSlot->GetSlotType() == EquipmentType && !FindSlot->bEquipped;
	});
	return *Slot;
}

void UTDEquipmentComponent::OnPrimarySlotChanged(UTDWeaponObject* WeaponObject, bool bEquipped)
{
	WeaponComponent->UpdateBeltWeapon(FName("Primary"), WeaponObject);
}

void UTDEquipmentComponent::OnSecondarySlotChanged(UTDWeaponObject* WeaponObject, bool bEquipped)
{
	WeaponComponent->UpdateBeltWeapon(FName("Secondary"), WeaponObject);
}
