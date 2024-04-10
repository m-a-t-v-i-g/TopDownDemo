// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDPlayerHUDWidget.generated.h"

class ATDCharacter;

UCLASS()
class TOPDOWNDEMO_API UTDPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
public:
	void InitHUDWidget(ATDCharacter* NewCharacter);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UWidgetSwitcher> WidgetSwitcher;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> HealthBar;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextAmmo;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTDInventoryWidget> InventoryWidget;

	UFUNCTION()
	FText GetAmmoInWeapon();
	
	UFUNCTION()
	float GetHealthPercent();

private:
	TWeakObjectPtr<ATDCharacter> Character;

public:
	void ToggleInventory();
};
