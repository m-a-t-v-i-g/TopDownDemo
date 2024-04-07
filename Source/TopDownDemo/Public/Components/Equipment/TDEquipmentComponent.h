// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDEquipmentComponent.generated.h"

UENUM(BlueprintType)
enum class ETDEquipmentType : uint8
{
	None,
	Main,
	Secondary
};

UCLASS(Blueprintable, BlueprintType, ClassGroup = "TopDownDemo")
class TOPDOWNDEMO_API UTDEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDEquipmentComponent();

	void AddEquipmentSlot(class UTDEquipmentSlot* Slot);

private:
	UPROPERTY(EditInstanceOnly, Category = "Equipment")
	TSet<UTDEquipmentSlot*> EquipmentSlots;
};
