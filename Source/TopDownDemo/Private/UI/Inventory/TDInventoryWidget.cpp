// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/TDInventoryWidget.h"
#include "TDInventoryComponent.h"
#include "Components/VerticalBox.h"
#include "Inventory/TDItemWidget.h"
#include "ItemSystem/Objects/TDItemObject.h"

void UTDInventoryWidget::InitInventoryWidget(UTDInventoryComponent* Inventory)
{
	Inventory->OnInventoryChangedDelegate.AddUObject(this, &UTDInventoryWidget::OnItemAdded);
}

void UTDInventoryWidget::OnItemAdded(UTDItemObject* ItemObject)
{
	UTDItemWidget* ItemWidget = CreateWidget<UTDItemWidget>(this, ItemWidgetClass);
	check(ItemWidget);

	ItemWidget->ItemObject = ItemObject;

	InventoryBox->AddChildToVerticalBox(ItemWidget);
}
