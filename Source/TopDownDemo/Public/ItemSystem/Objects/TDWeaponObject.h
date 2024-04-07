﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItemObject.h"
#include "TDWeaponObject.generated.h"

class ATDWeaponActor;

USTRUCT(BlueprintType)
struct FTDWeaponParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Properties")
	int Rounds = 0;
};

UCLASS()
class TOPDOWNDEMO_API UTDWeaponObject : public UTDItemObject
{
	GENERATED_BODY()

public:
	void operator=(const ATDWeaponActor* WeaponActor);
	
protected:
	UPROPERTY(EditAnywhere, Category = "Weapon")
	FTDWeaponParams WeaponParams;
};
