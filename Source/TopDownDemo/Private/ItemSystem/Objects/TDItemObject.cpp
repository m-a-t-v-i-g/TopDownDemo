// Fill out your copyright notice in the Description page of Project Settings.

#include "Objects/TDItemObject.h"
#include "TDItemActor.h"

void UTDItemObject::operator=(const ATDItemActor* ItemActor)
{
	ItemAsset = ItemActor->GetItemAsset();
	ItemParams = ItemActor->GetItemParams();
	ItemClass = ItemActor->GetClass();
}
