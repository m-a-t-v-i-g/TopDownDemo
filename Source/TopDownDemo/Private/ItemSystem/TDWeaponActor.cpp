/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

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
		if (FindEquipment->IsAnySlotAvailableFor(WeaponObject))
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
	if (IsAmmoFull()) return;
	
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
		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("Weapon needs to reload!")), true, false);
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

bool ATDWeaponActor::IsAmmoFull()
{
	return WeaponParams.Rounds == GetWeaponAsset()->MaxRounds;
}
