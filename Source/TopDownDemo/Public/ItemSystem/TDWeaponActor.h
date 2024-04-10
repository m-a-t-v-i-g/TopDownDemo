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

	virtual void InitItem(UTDItemObject* ItemObject) override;

	virtual UTDItemObject* CreateItemObject(UClass* WeaponObjectClass) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<class UArrowComponent> Muzzle;
	
	UPROPERTY(EditInstanceOnly, Category = "Weapon")
	FTDWeaponParams WeaponParams;

public:
	void StartShot();
	void StopShot();

	void StartReload();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	FORCEINLINE FTDWeaponParams GetWeaponParams() const { return WeaponParams; }

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FHitResult ShotLocation;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void MakeShot();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void MakeReload();
	
private:
	FTimerHandle ShotTimerHandle;
	FTimerHandle ReloadTimerHandle;

public:
	UFUNCTION()
	class UTDWeaponAsset* GetWeaponAsset() const;

	UFUNCTION()
	bool CanShot();

	UFUNCTION()
	bool IsAmmoEmpty();

	UFUNCTION()
	bool IsAmmoFull();

	bool bIsReloading = false;
};
