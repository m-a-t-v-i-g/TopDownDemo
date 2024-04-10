// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItemAsset.h"
#include "TDAmmoAsset.generated.h"

UCLASS()
class TOPDOWNDEMO_API UTDAmmoAsset : public UTDItemAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammo", meta = (ClampMin = "0", ForceUnits = "pc"))
	int MaxAmmo = 0;
};
