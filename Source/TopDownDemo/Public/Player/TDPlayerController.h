// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDPlayerController.generated.h"

struct FInputActionValue;

class UInputMappingContext;
class UTDInteractionComponent;
class ATDCharacter;

UCLASS()
class TOPDOWNDEMO_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATDPlayerController();

#pragma region Components
	
public:
	virtual void PreInitializeComponents() override final;

	/** Класс компонента взаимодействия на случай, если не создан экземпляр из блупринта. */
	UPROPERTY(EditAnywhere, Category = "Interaction")
	TSubclassOf<UTDInteractionComponent> InteractionComponentClass;
	
	static FName InteractionComponentName;
	
protected:
	/** Компонент для взаимодействия с окружением. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	TObjectPtr<UTDInteractionComponent> InteractionComponent;
	
	/** Аналог PreInitializeComponents для возможности создания компонентов из блупринтов. */
	virtual void FindOrCreateComponents();

	virtual void PostInitializeComponents() override;
	
#pragma endregion Components

#pragma region Input

public:
	virtual void SetupInputComponent() override;
	
protected:
	/** Контекст инпута. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputMappingContext> InputContext;

	/** Метод бинда инпутов. */
	virtual void BindActions(UInputMappingContext* Context);

	/** Метод обработки клика левой клавиши мыши. */
	UFUNCTION()
	void IA_LeftClick(const FInputActionValue& Value);

	/* Метод обработки клика правой клавиши мыши. */
	UFUNCTION()
	void IA_RightClick(const FInputActionValue& Value);

	/* Включение/отключение инвентаря. */
	UFUNCTION()
	void IA_ToggleInventory(const FInputActionValue& Value);

#pragma endregion Input

	virtual void OnPossess(APawn* InPawn) override;
	
	void OnInteraction(AActor* TargetActor);
	void OnAction();

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Pawn")
	ATDCharacter* GetTDCharacter();
};
