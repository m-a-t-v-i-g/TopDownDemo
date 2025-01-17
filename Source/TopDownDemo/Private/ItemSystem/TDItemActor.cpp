﻿/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "TDItemActor.h"
#include "TDInventoryComponent.h"
#include "Assets/TDItemAsset.h"
#include "Components/SphereComponent.h"
#include "Objects/TDItemObject.h"

ATDItemActor::ATDItemActor()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("SphereCollision"));
	SetRootComponent(SphereCollision);

	SphereCollision->SetSphereRadius(6.0f);
	SphereCollision->SetSimulatePhysics(true);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	
	PrimaryActorTick.bCanEverTick = true;
}

void ATDItemActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ATDItemActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!IsValid(ItemAsset)) return;
	
	StaticMesh->SetStaticMesh(ItemAsset->GetStaticMesh());
}

void ATDItemActor::OnInteraction(AActor* Interactor)
{
	if (UTDInventoryComponent* FindInventory = Interactor->FindComponentByClass<UTDInventoryComponent>())
	{
		UTDItemObject* ItemObject = CreateItemObject(UTDItemObject::StaticClass());
		check(ItemObject);
		
		FindInventory->AddItem(ItemObject);
		Destroy();
	}
}

void ATDItemActor::InitItem(UTDItemObject* ItemObject)
{
	ItemAsset = ItemObject->GetItemAsset();
	ItemParams = ItemObject->GetItemParams();
}

UTDItemObject* ATDItemActor::CreateItemObject(UClass* ItemObjectClass)
{
	UTDItemObject* CreatedItemObject = nullptr;
	if (ItemObjectClass->IsChildOf<UTDItemObject>())
	{
		CreatedItemObject = NewObject<UTDItemObject>(GetTransientPackage(), ItemObjectClass);
		*CreatedItemObject = this;
	}
	return CreatedItemObject;
}

void ATDItemActor::SetHandedMode()
{
	SphereCollision->SetSimulatePhysics(false);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
