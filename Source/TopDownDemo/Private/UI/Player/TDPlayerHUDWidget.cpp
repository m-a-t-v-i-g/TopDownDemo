// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/TDPlayerHUDWidget.h"
#include "TDCharacter.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Inventory/TDInventoryWidget.h"

void UTDPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	HealthBar->PercentDelegate.BindDynamic(this, &UTDPlayerHUDWidget::GetHealthPercent);
	TextAmmo->TextDelegate.BindDynamic(this, &UTDPlayerHUDWidget::GetAmmoInWeapon);
}

void UTDPlayerHUDWidget::InitHUDWidget(ATDCharacter* NewCharacter)
{
	Character = NewCharacter;
	
	InventoryWidget->InitInventoryWidget(Character->GetInventoryComponent());
}

FText UTDPlayerHUDWidget::GetAmmoInWeapon()
{
	if (!Character.IsValid() || !Character->IsArmed())
	{
		return FText();
	}
	return FText::FromString(FString::FromInt(Character->GetAmmoInWeapon()));
}

float UTDPlayerHUDWidget::GetHealthPercent()
{
	if (!Character.IsValid())
	{
		return 0.0f;
	}
	return Character->GetHealthPercent();
}

void UTDPlayerHUDWidget::ToggleInventory()
{
	switch (WidgetSwitcher->GetActiveWidgetIndex())
	{
	case 0:
		{
			WidgetSwitcher->SetActiveWidgetIndex(1);
			break;
		}
	default:
		{
			WidgetSwitcher->SetActiveWidgetIndex(0);
			break;
		}
	}
}
