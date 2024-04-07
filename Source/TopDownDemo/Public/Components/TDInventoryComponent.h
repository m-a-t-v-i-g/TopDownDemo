// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDInventoryComponent.generated.h"

class UTDItemAsset;
class UTDItemObject;

UCLASS(Blueprintable, BlueprintType, ClassGroup = "TopDownDemo")
class TOPDOWNDEMO_API UTDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDInventoryComponent();

	void AddItem(UTDItemObject* ItemObject);

protected:
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	TArray<UTDItemObject*> InventoryItems;
};
