// Fill out your copyright notice in the Description page of Project Settings.

#include "TDWeaponActor.h"
#include "TDInventoryComponent.h"
#include "Assets/TDWeaponAsset.h"
#include "Components/ArrowComponent.h"
#include "Equipment/TDEquipmentComponent.h"
#include "Kismet/KismetSystemLibrary.h"
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
	if (IsAmmoEmpty())
	{
		StartReload();
		return;
	}

	if (CanShot())
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
}

void ATDWeaponActor::StopShot()
{
	if (GetWeaponAsset()->bAutomatic)
	{
		GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	}
}

void ATDWeaponActor::StartReload()
{
	bIsReloading = true;
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &ATDWeaponActor::MakeReload, GetWeaponAsset()->ReloadTime, false);
	UKismetSystemLibrary::PrintString(GetWorld(), "Reloading...", true, false);
}

void ATDWeaponActor::MakeShot_Implementation()
{
	if (!IsAmmoEmpty())
	{
		WeaponParams.Rounds--;
	}
	else
	{
		StopShot();
		StartReload();
	}
}

void ATDWeaponActor::MakeReload_Implementation()
{
	bIsReloading = false;
	WeaponParams.Rounds = GetWeaponAsset()->MaxRounds;
	GetWorldTimerManager().ClearTimer(ReloadTimerHandle);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%s was reload!"), *GetName()), true, false);
}

UTDWeaponAsset* ATDWeaponActor::GetWeaponAsset() const
{
	return Cast<UTDWeaponAsset>(ItemAsset);
}

bool ATDWeaponActor::CanShot()
{
	return !bIsReloading && WeaponParams.Rounds > 0;
}

bool ATDWeaponActor::IsAmmoEmpty()
{
	return WeaponParams.Rounds <= 0;
}
