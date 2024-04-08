// Fill out your copyright notice in the Description page of Project Settings.

#include "Equipment/TDEquipmentComponent.h"

#include "TDCharacter.h"
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

void UTDEquipmentComponent::InitEquipment()
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

void UTDEquipmentComponent::UnequipItem(UTDWeaponObject* WeaponObject)
{
	auto DataAsset = Cast<UTDWeaponAsset>(WeaponObject->GetItemAsset());
	if (!DataAsset)
	{
		return;
	}

	auto Slot = *EquipmentSlots.FindByPredicate([WeaponObject](const UTDEquipmentSlot* FindSlot)
	{
		return FindSlot->GetWeaponObject() == WeaponObject;
	});
	
	Slot->UnequipSlot(WeaponObject);
	EquippedItems.Remove(Slot);
}

bool UTDEquipmentComponent::IsAnySlotAvailable(const UTDWeaponObject* WeaponObject)
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
	const FString FunctionName = FString(TEXT("On")) + FString(SlotToBind->GetSlotName().ToString()) + FString(TEXT("SlotChanged"));
	SlotToBind->OnSlotChangedDelegate.AddUFunction(this, FName(*FunctionName));
}

UTDEquipmentSlot* UTDEquipmentComponent::GetSlotByType(ETDEquipmentType EquipmentType)
{
	auto Slot = EquipmentSlots.FindByPredicate([EquipmentType](UTDEquipmentSlot* FindSlot)
	{
		return FindSlot->GetSlotType() == EquipmentType;
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
