// Fill out your copyright notice in the Description page of Project Settings.

#include "TDWeaponComponent.h"
#include "TDWeaponActor.h"
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
		WeaponSlot->WeaponObject.Reset();	
	}
	
	if (!IsValid(WeaponObject)) return;

	ATDWeaponActor* BeltWeapon = SpawnWeaponOnBelt(WeaponObject);
	check(BeltWeapon);

	BeltMap.Find(SlotName)->WeaponActor = BeltWeapon;
}

ATDWeaponActor* UTDWeaponComponent::SpawnWeaponOnBelt(UTDWeaponObject* FromObject)
{
	ATDWeaponActor* SpawnedBeltFirst = GetWorld()->SpawnActor<ATDWeaponActor>(FromObject->ItemClass);
	if (SpawnedBeltFirst)
	{
		
		/*
		FAttachmentTransformRules AttachmentTransformRules {EAttachmentRule::SnapToTarget, false};
		SpawnedBeltFirst->AttachToComponent(Character->GetMesh(), AttachmentTransformRules, AttachmentPoint);
		SpawnedBeltFirst->FinishSpawning(SpawnTransform);
		*/
		
	}
	return SpawnedBeltFirst;
}

bool UTDWeaponComponent::HasBeltWeapon(FName SlotName)
{
	auto WeaponSlot = BeltMap.Find(SlotName);
	if (!WeaponSlot)
	{
		return false;
	}
	return WeaponSlot->WeaponObject.IsValid();
}
