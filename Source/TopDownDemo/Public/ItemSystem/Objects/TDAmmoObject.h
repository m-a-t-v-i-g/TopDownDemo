// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItemObject.h"
#include "TDAmmoObject.generated.h"

class ATDAmmoActor;

USTRUCT(BlueprintType)
struct FTDAmmoParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Properties")
	int Ammo = 0;
};

UCLASS()
class TOPDOWNDEMO_API UTDAmmoObject : public UTDItemObject
{
	GENERATED_BODY()

public:
	void operator=(const ATDAmmoActor* AmmoActor);
	
protected:
	UPROPERTY(EditAnywhere, Category = "Ammo")
	FTDAmmoParams AmmoParams;
};
