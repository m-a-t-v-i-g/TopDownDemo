// Fill out your copyright notice in the Description page of Project Settings.

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
	
#pragma endregion Components

#pragma region Cache
	
private:
	TWeakObjectPtr<class UPathFollowingComponent> FollowingComponent;
	TWeakObjectPtr<AActor> TargetToInteract;
	
	FDelegateHandle StopMovingDelegate;

#pragma endregion Cache

public:
	virtual void PossessedBy(AController* NewController) override;
	
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	void TryInteract(AActor* WithActor);

private:
	void ProcessInteraction();
	void InteractAfterMoving(FAIRequestID RequestID, const FPathFollowingResult& FollowResult);

public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

	void OnCharacterDead();
	
	UPROPERTY(EditAnywhere, Category = "Health")
	bool bIsDead = false;
};
