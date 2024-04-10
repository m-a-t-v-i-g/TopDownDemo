// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItemAsset.h"
#include "TDMedAsset.generated.h"

UCLASS()
class TOPDOWNDEMO_API UTDMedAsset : public UTDItemAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (ClampMin = "0", ForceUnits = "hp"))
	float HealValue = 0.0f;
};
