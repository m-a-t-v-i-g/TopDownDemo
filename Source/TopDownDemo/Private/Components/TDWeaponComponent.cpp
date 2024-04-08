// Fill out your copyright notice in the Description page of Project Settings.

#include "TDWeaponComponent.h"
#include "TDWeaponActor.h"
#include "GameFramework/Character.h"
#include "Objects/TDWeaponObject.h"

UTDWeaponComponent::UTDWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDWeaponComponent::UpdateBeltWeapon(FName SlotName, UTDWeaponObject* WeaponObject)
{
	if (HasBeltWeapon(SlotName))
	{
		auto WeaponSlot = BeltMap.Find(SlotName);
		if (!WeaponSlot)
		{
			return;
		}
	}
	
	if (!IsValid(WeaponObject)) return;

	ATDWeaponActor* BeltWeapon = SpawnWeaponOnBelt(SlotName, WeaponObject);
	check(BeltWeapon);

	BeltMap.Find(SlotName)->WeaponActor = BeltWeapon;
}

ATDWeaponActor* UTDWeaponComponent::SpawnWeaponOnBelt(FName SlotName, UTDWeaponObject* FromObject)
{
	ATDWeaponActor* Weapon = nullptr;
	if (auto WeaponSlot = BeltMap.Find(SlotName))
	{
		ACharacter* Character = Cast<ACharacter>(GetOwner());
		Weapon = GetWorld()->SpawnActor<ATDWeaponActor>(FromObject->ItemClass);
		
		if (Weapon)
		{
			FAttachmentTransformRules AttachmentTransformRules{EAttachmentRule::SnapToTarget, false};
			Weapon->InitItem(FromObject);
			Weapon->SetHandedMode();
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentTransformRules, WeaponSlot->SocketName);
		}
	}
	return Weapon;
}

bool UTDWeaponComponent::HasBeltWeapon(FName SlotName)
{
	auto WeaponSlot = BeltMap.Find(SlotName);
	if (!WeaponSlot)
	{
		return false;
	}
	return WeaponSlot->WeaponActor.IsValid();
}
