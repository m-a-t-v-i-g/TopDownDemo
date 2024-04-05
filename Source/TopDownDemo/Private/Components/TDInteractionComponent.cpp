// Fill out your copyright notice in the Description page of Project Settings.

#include "TDInteractionComponent.h"
#include "TDInteractionInterface.h"
#include "Kismet/KismetSystemLibrary.h"

UTDInteractionComponent::UTDInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDInteractionComponent::ProcessInteraction(const FHitResult& HitResult)
{
	AActor* HitActor = HitResult.GetActor();
	if (!IsValid(HitActor)) return;

	if (HitActor->Implements<UTDInteractionInterface>())
	{
		OnInteractionDelegate.Broadcast(HitActor);
		UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Target actor: %s."), *HitActor->GetName()), true, false);
	}
}
