/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

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

	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	FVector ShotLocation;

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void MakeShot();

	UFUNCTION(BlueprintNativeEvent, Category = "Weapon")
	void MakeReload();
	
public:
	UPROPERTY(BlueprintReadOnly, Category = "Weapon")
	bool bIsReloading = false;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	class UTDWeaponAsset* GetWeaponAsset() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	FORCEINLINE FTDWeaponParams GetWeaponParams() const { return WeaponParams; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	bool CanShot();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	bool IsAmmoEmpty();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Weapon")
	bool IsAmmoFull();
	
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void MakeAmmoFull();
	
private:
	FTimerHandle ShotTimerHandle;
	FTimerHandle ReloadTimerHandle;
};
