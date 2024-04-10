// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/TDAmmoObject.h"
#include "TDAmmoActor.h"

void UTDAmmoObject::operator=(const ATDAmmoActor* AmmoActor)
{
	ItemAsset = AmmoActor->GetItemAsset();
	ItemParams = AmmoActor->GetItemParams();
	AmmoParams = AmmoActor->GetAmmoParams();
}
