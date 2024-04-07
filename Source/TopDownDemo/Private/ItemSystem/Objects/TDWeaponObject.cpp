// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/TDWeaponObject.h"
#include "TDWeaponActor.h"

void UTDWeaponObject::operator=(const ATDWeaponActor* WeaponActor)
{
	ItemAsset = WeaponActor->GetItemAsset();
	ItemParams = WeaponActor->GetItemParams();
	WeaponParams = WeaponActor->GetWeaponParams();
}
