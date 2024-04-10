// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/TDInventoryWidget.h"
#include "TDInventoryComponent.h"
#include "Components/VerticalBox.h"
#include "Inventory/TDItemWidget.h"
#include "ItemSystem/Objects/TDItemObject.h"

void UTDInventoryWidget::InitInventoryWidget(UTDInventoryComponent* Inventory)
{
	Inventory->OnItemAdded.AddUObject(this, &UTDInventoryWidget::OnItemAdded);
	Inventory->OnItemRemoved.AddUObject(this, &UTDInventoryWidget::OnItemRemoved);
}

void UTDInventoryWidget::OnItemAdded(UTDItemObject* ItemObject)
{
	UTDItemWidget* ItemWidget = CreateWidget<UTDItemWidget>(this, ItemWidgetClass);
	check(ItemWidget);

	ItemWidget->ItemObject = ItemObject;

	InventoryBox->AddChildToVerticalBox(ItemWidget);
	ItemsMap.Add(ItemObject, ItemWidget);
}

void UTDInventoryWidget::OnItemRemoved(UTDItemObject* ItemObject)
{
	auto ItemWidget = *ItemsMap.Find(ItemObject);
	ItemWidget->RemoveFromParent();

	ItemsMap.Remove(ItemObject);
}
