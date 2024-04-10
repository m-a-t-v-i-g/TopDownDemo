// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItemActor.h"
#include "Objects/TDAmmoObject.h"
#include "TDAmmoActor.generated.h"

UCLASS()
class TOPDOWNDEMO_API ATDAmmoActor : public ATDItemActor
{
	GENERATED_BODY()

public:
	ATDAmmoActor();

	virtual void OnInteraction(AActor* Interactor) override;
	
	virtual UTDItemObject* CreateItemObject(UClass* AmmoObjectClass) override;
	
protected:
	UPROPERTY(EditInstanceOnly, Category = "Ammo")
	FTDAmmoParams AmmoParams;

public:	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ammo")
	FORCEINLINE FTDAmmoParams GetAmmoParams() const { return AmmoParams; }
};
