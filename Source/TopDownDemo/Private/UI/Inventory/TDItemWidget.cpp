// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/TDItemWidget.h"
#include "Assets/TDItemAsset.h"
#include "Components/TextBlock.h"
#include "Objects/TDItemObject.h"

void UTDItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	TextItemName->TextDelegate.BindDynamic(this, &UTDItemWidget::GetItemName);
}

FText UTDItemWidget::GetItemName()
{
	return ItemObject->GetItemAsset()->GetItemName();
}
