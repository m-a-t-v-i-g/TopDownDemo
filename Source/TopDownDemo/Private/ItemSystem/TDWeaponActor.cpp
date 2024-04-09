// Fill out your copyright notice in the Description page of Project Settings.

#include "TDWeaponActor.h"
#include "TDInventoryComponent.h"
#include "Assets/TDWeaponAsset.h"
#include "Components/ArrowComponent.h"
#include "Equipment/TDEquipmentComponent.h"
#include "Objects/TDWeaponObject.h"

ATDWeaponActor::ATDWeaponActor()
{
	Muzzle = CreateDefaultSubobject<UArrowComponent>("Muzzle");
	Muzzle->SetupAttachment(GetRootComponent());
	
	PrimaryActorTick.bCanEverTick = true;
}

void ATDWeaponActor::OnInteraction(AActor* Interactor)
{
	UTDWeaponObject* WeaponObject = Cast<UTDWeaponObject>(CreateItemObject(UTDWeaponObject::StaticClass()));
	check(WeaponObject);

	if (UTDEquipmentComponent* FindEquipment = Interactor->FindComponentByClass<UTDEquipmentComponent>())
	{
		if (FindEquipment->IsAnySlotAvailable(WeaponObject))
		{
			FindEquipment->EquipItem(WeaponObject);
			Destroy();
			return;
		}
	}
	
	if (UTDInventoryComponent* FindInventory = Interactor->FindComponentByClass<UTDInventoryComponent>())
	{
		FindInventory->AddItem(WeaponObject);
		Destroy();
		return;
	}

	WeaponObject->MarkAsGarbage();
}

void ATDWeaponActor::InitItem(UTDItemObject* ItemObject)
{
	Super::InitItem(ItemObject);

	auto WeaponObject = Cast<UTDWeaponObject>(ItemObject);
	if (!WeaponObject)
	{
		return;
	}

	WeaponParams = WeaponObject->GetWeaponParams();
}

UTDItemObject* ATDWeaponActor::CreateItemObject(UClass* WeaponObjectClass)
{
	UTDWeaponObject* CreatedWeaponObject = nullptr;
	if (WeaponObjectClass->IsChildOf<UTDWeaponObject>())
	{
		CreatedWeaponObject = Cast<UTDWeaponObject>(Super::CreateItemObject(WeaponObjectClass));
		*CreatedWeaponObject = this;
	}
	return CreatedWeaponObject;
}

void ATDWeaponActor::StartShot()
{
	if (GetWeaponAsset()->bAutomatic)
	{
		float ShotDelay = 1.0f / (GetWeaponAsset()->FireRate / 60.0f);
		GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ATDWeaponActor::MakeShot, ShotDelay, true);
	}
	else
	{
		MakeShot();
	}
}

void ATDWeaponActor::StopShot()
{
	if (GetWeaponAsset()->bAutomatic)
	{
		GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	}
}

void ATDWeaponActor::MakeShot_Implementation()
{
	
}

UTDWeaponAsset* ATDWeaponActor::GetWeaponAsset() const
{
	return Cast<UTDWeaponAsset>(ItemAsset);
}
