// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDCharacter.generated.h"

struct FAIRequestID;
struct FPathFollowingResult;

class UTDInventoryComponent;

UCLASS()
class TOPDOWNDEMO_API ATDCharacter : public ACharacter
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
	
protected:
	/** Компонент инвентаря. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TObjectPtr<UTDInventoryComponent> InventoryComponent;

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
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	void TryInteract(AActor* WithActor);

private:
	void ProcessInteraction();
	void InteractAfterMoving(FAIRequestID RequestID, const FPathFollowingResult& FollowResult);
};
