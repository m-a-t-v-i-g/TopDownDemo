// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/TDMedObject.h"
#include "TDMedActor.h"
#include "Assets/TDMedAsset.h"

void UTDMedObject::operator=(const ATDMedActor* MedActor)
{
	ItemAsset = MedActor->GetItemAsset();
	ItemParams = MedActor->GetItemParams();
}

float UTDMedObject::GetHealValue()
{
	auto MedAsset = Cast<UTDMedAsset>(ItemAsset);
	return MedAsset->HealValue;
}
