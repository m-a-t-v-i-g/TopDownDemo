// Fill out your copyright notice in the Description page of Project Settings.

#include "TDAmmoActor.h"
#include "TDInventoryComponent.h"

ATDAmmoActor::ATDAmmoActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATDAmmoActor::OnInteraction(AActor* Interactor)
{
	UTDAmmoObject* AmmoObject = Cast<UTDAmmoObject>(CreateItemObject(UTDAmmoObject::StaticClass()));
	check(AmmoObject);

	if (UTDInventoryComponent* FindInventory = Interactor->FindComponentByClass<UTDInventoryComponent>())
	{
		FindInventory->AddItem(AmmoObject);
		Destroy();
		return;
	}

	AmmoObject->MarkAsGarbage();
}

UTDItemObject* ATDAmmoActor::CreateItemObject(UClass* AmmoObjectClass)
{
	UTDAmmoObject* CreatedAmmoObject = nullptr;
	if (AmmoObjectClass->IsChildOf<UTDAmmoObject>())
	{
		CreatedAmmoObject = Cast<UTDAmmoObject>(Super::CreateItemObject(AmmoObjectClass));
		*CreatedAmmoObject = this;
	}
	return CreatedAmmoObject;
}
