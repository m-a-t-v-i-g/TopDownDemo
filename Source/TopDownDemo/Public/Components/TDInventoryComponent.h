// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDInventoryComponent.generated.h"

class UTDItemAsset;

UCLASS(Blueprintable, BlueprintType)
class TOPDOWNDEMO_API UTDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDInventoryComponent();

protected:
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	TMap<UTDItemAsset*, int> InventoryItems;
};
