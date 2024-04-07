// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItemActor.h"
#include "Objects/TDWeaponObject.h"
#include "TDWeaponActor.generated.h"

UCLASS()
class TOPDOWNDEMO_API ATDWeaponActor : public ATDItemActor
{
	GENERATED_BODY()

public:
	ATDWeaponActor();

	virtual void OnInteraction(AActor* Interactor) override;

	virtual UTDItemObject* CreateItemObject(UClass* WeaponObjectClass) override;
	
protected:
	UPROPERTY(EditInstanceOnly, Category = "Weapon")
	FTDWeaponParams WeaponParams;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE FTDWeaponParams GetWeaponParams() const { return WeaponParams; }
};
