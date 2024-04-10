// Fill out your copyright notice in the Description page of Project Settings.

#include "TDWeaponComponent.h"
#include "TDCharacter.h"
#include "TDInventoryComponent.h"
#include "TDWeaponActor.h"
#include "Assets/TDAmmoAsset.h"
#include "Assets/TDWeaponAsset.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Objects/TDWeaponObject.h"

UTDWeaponComponent::UTDWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsShooting) return;
	
	ATDCharacter* Character = Cast<ATDCharacter>(GetOwner());
	if (!Character) return;
	
	ShotLocation = Character->GetHitResultUnderCursor();
	HandedWeapon->ShotLocation = ShotLocation;
}

void UTDWeaponComponent::InitWeaponComponent(ATDCharacter* Character)
{
	Inventory = Character->GetInventoryComponent();
}

void UTDWeaponComponent::UpdateHandedWeapon(int SlotIndex)
{
	ATDCharacter* Character = Cast<ATDCharacter>(GetOwner());

	FName MovingSlot;
	
	if (HasHandedWeapon())
	{
		MoveHandedWeaponToBelt(MovingSlot);
	}

	FTransform AttachmentTransform = Character->GetMesh()->GetSocketTransform(HandAttachPoint);
	switch (SlotIndex)
	{
	case 1:
		{
			if (!HasBeltWeapon("Primary") || MovingSlot == "Primary") return;
			
			auto WeaponSlot = BeltMap.Find(FName("Primary"));
			if (!WeaponSlot)
			{
				return;
			}

			auto BeltPrimaryWeapon = WeaponSlot->WeaponActor;
			
			FAttachmentTransformRules AttachmentTransformRules {EAttachmentRule::SnapToTarget, false};
			
			BeltPrimaryWeapon->AttachToComponent(Character->GetMesh(), AttachmentTransformRules, HandAttachPoint);
			BeltPrimaryWeapon->SetActorTransform(AttachmentTransform);
			HandedWeapon = BeltPrimaryWeapon.Get();
			break;
		}
	case 2:
		{
			if (!HasBeltWeapon("Secondary") || MovingSlot == "Secondary") return;
			
			auto WeaponSlot = BeltMap.Find(FName("Secondary"));
			if (!WeaponSlot)
			{
				return;
			}

			auto BeltSecondaryWeapon = WeaponSlot->WeaponActor;
			
			FAttachmentTransformRules AttachmentTransformRules {EAttachmentRule::SnapToTarget, false};
			
			BeltSecondaryWeapon->AttachToComponent(Character->GetMesh(), AttachmentTransformRules, HandAttachPoint);
			BeltSecondaryWeapon->SetActorTransform(AttachmentTransform);
			HandedWeapon = BeltSecondaryWeapon.Get();
			break;
		}
	default: break;
	}
}

void UTDWeaponComponent::MoveHandedWeaponToBelt(FName& MovingSlot)
{
	ATDCharacter* Character = Cast<ATDCharacter>(GetOwner());

	auto DataAsset = Cast<UTDWeaponAsset>(HandedWeapon->GetItemAsset());
	check(DataAsset);

	FName WeaponSlotName;
	
	switch (DataAsset->EquipmentType)
	{
	case ETDEquipmentType::Primary:
		{
			WeaponSlotName = "Primary";
			break;
		}
	case ETDEquipmentType::Secondary:
		{
			WeaponSlotName = "Secondary";
			break;
		}
	default: break;
	}

	MovingSlot = WeaponSlotName;
	
	auto WeaponSlot = BeltMap.Find(WeaponSlotName);
	check(WeaponSlot);
	
	FTransform AttachmentTransform = Character->GetMesh()->GetSocketTransform(WeaponSlot->SocketName);
	FAttachmentTransformRules AttachmentTransformRules {EAttachmentRule::SnapToTarget, false};
	
	HandedWeapon->AttachToComponent(Character->GetMesh(), AttachmentTransformRules, WeaponSlot->SocketName);
	HandedWeapon->SetActorTransform(AttachmentTransform);
	HandedWeapon = nullptr;
}

void UTDWeaponComponent::StartShot()
{
	if (!HasHandedWeapon()) return;

	if (HandedWeapon->IsAmmoEmpty())
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Weapon needs to reload!")), true, false);
	}
	else if (HandedWeapon->CanShot())
	{
		HandedWeapon->StartShot();
		bIsShooting = true;
	}
}

void UTDWeaponComponent::StopShot()
{
	if (!HasHandedWeapon()) return;
	
	HandedWeapon->StopShot();
	bIsShooting = false;
}

void UTDWeaponComponent::StartReload()
{
	if (!HasHandedWeapon()) return;

	if (HandedWeapon->bIsReloading) return;
	
	auto WeaponAsset = HandedWeapon->GetWeaponAsset();
	
	if (!Inventory->FindItemByAsset(WeaponAsset->AmmoType))
	{
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("No available ammo in the inventory!")), true, false);
		return;
	}
	
	if (!HandedWeapon->IsAmmoFull())
	{
		HandedWeapon->StartReload();
	}
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
			Weapon->SetOwner(GetOwner());
			Weapon->SetHandedMode();
			Weapon->AttachToComponent(Character->GetMesh(), AttachmentTransformRules, WeaponSlot->SocketName);
		}
	}
	return Weapon;
}

bool UTDWeaponComponent::HasHandedWeapon()
{
	return IsValid(HandedWeapon);
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
