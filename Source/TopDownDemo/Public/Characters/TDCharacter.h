/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "TDSavableInterface.h"
#include "GameFramework/Character.h"
#include "TDCharacter.generated.h"

struct FAIRequestID;
struct FPathFollowingResult;

class UTDInventoryComponent;
class UTDEquipmentComponent;
class UTDWeaponComponent;
class UTDHealthComponent;

UCLASS()
class TOPDOWNDEMO_API ATDCharacter : public ACharacter, public ITDSavableInterface
{
	GENERATED_BODY()

public:
	ATDCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
							 AActor* DamageCauser) override;
	virtual void Destroyed() override;

#pragma region Components
	
public:
	virtual void PreInitializeComponents() override final;

	/** Класс компонента инвентаря на случай, если не создан экземпляр из блупринта. */
	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<UTDInventoryComponent> InventoryComponentClass;
	
	static FName InventoryComponentName;
	
	/** Класс компонента экипировки на случай, если не создан экземпляр из блупринта. */
	UPROPERTY(EditAnywhere, Category = "Equipment")
	TSubclassOf<UTDEquipmentComponent> EquipmentComponentClass;
	
	static FName EquipmentComponentName;
	
	/** Класс компонента оружия на случай, если не создан экземпляр из блупринта. */
	UPROPERTY(EditAnywhere, Category = "Weapon")
	TSubclassOf<UTDWeaponComponent> WeaponComponentClass;
	
	static FName WeaponComponentName;
	
	/** Класс компонента здоровья на случай, если не создан экземпляр из блупринта. */
	UPROPERTY(EditAnywhere, Category = "Health")
	TSubclassOf<UTDHealthComponent> HealthComponentClass;
	
	static FName HealthComponentName;
	
protected:
	/** Компонент инвентаря. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UTDInventoryComponent> InventoryComponent;
	
	/** Компонент экипировки. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Equipment")
	TObjectPtr<UTDEquipmentComponent> EquipmentComponent;

	/** Компонент оружия. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UTDWeaponComponent> WeaponComponent;

	/** Компонент здоровья. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	TObjectPtr<UTDHealthComponent> HealthComponent;

	/** Аналог PreInitializeComponents для возможности создания компонентов из блупринтов. */
	virtual void FindOrCreateComponents();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character|Inventory")
	UTDInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	
#pragma endregion Components

#pragma region Cache
	
private:
	TWeakObjectPtr<class UPathFollowingComponent> FollowingComponent;
	TWeakObjectPtr<AActor> TargetToInteract;

	FDelegateHandle StopMovingDelegate;

public:
	FHitResult GetHitResultUnderCursor();

#pragma endregion Cache

#pragma region Interaction
	
public:
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	void TryInteract(AActor* WithActor);

	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	void ChooseAction();

	UFUNCTION(BlueprintCallable, Category = "Character|Weapon")
	void ForceStopShooting();

private:
	void ProcessInteraction();
	void InteractAfterMoving(FAIRequestID RequestID, const FPathFollowingResult& FollowResult);
	
#pragma endregion Interaction

public:
	UFUNCTION(BlueprintCallable, Category = "Character|Weapon")
	void ReloadWeapon();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character|Weapon")
	bool IsArmed();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character|Weapon")
	int GetAmmoInWeapon();

	UPROPERTY(EditAnywhere, Category = "Health")
	bool bIsDead = false;

	UFUNCTION(BlueprintCallable, Category = "Character|Health")
	void UseMedkit();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Character|Health")
	float GetHealthPercent();
	
	void OnCharacterDead();
};
