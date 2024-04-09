// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/TDPlayerHUD.h"

#include "TDCharacter.h"
#include "Player/TDPlayerHUDWidget.h"

void ATDPlayerHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UTDPlayerHUDWidget>(GetOwningPlayerController(), HUDWidgetClass, FName("HUDWidget"));
	}
	
	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}

	if (GetOwningPlayerController())
	{
		GetOwningPlayerController()->OnPossessedPawnChanged.AddDynamic(this, &ATDPlayerHUD::OnNewPawn);
	}
}

void ATDPlayerHUD::OnNewPawn(APawn* OldPawn, APawn* NewPawn)
{
	if (NewPawn == OldPawn || !NewPawn) return;

	HUDWidget->InitHUDWidget(Cast<ATDCharacter>(NewPawn));
}

void ATDPlayerHUD::ToggleInventory()
{
	HUDWidget->ToggleInventory();
}
