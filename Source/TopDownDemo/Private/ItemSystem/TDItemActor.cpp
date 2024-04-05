// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemSystem/TDItemActor.h"
#include "Components/SphereComponent.h"
#include "ItemSystem/Assets/TDItemAsset.h"

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

void ATDItemActor::OnInteraction()
{
	ITDInteractionInterface::OnInteraction();
}
