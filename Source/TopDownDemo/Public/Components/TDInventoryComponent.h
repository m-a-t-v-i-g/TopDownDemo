// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Assets/TDWeaponAsset.h"
#include "Components/ActorComponent.h"
#include "TDInventoryComponent.generated.h"

class UTDMedObject;
class UTDItemAsset;
class UTDItemObject;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemAdded, UTDItemObject*);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnItemRemoved, UTDItemObject*);

UCLASS(Blueprintable, BlueprintType, ClassGroup = "TopDownDemo")
class TOPDOWNDEMO_API UTDInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDInventoryComponent();

	void AddItem(UTDItemObject* ItemObject);

	void RemoveItem(UTDItemObject* ItemObject);

	UTDItemObject* FindItemByAsset(UTDItemAsset* AssetType);

	UTDItemObject* FindMedkit();
	
private:
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	TArray<UTDItemObject*> InventoryItems;

public:
	FOnItemAdded OnItemAdded;
	FOnItemRemoved OnItemRemoved;
};
