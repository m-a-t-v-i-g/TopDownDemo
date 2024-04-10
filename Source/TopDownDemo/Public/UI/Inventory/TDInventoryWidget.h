// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDInventoryWidget.generated.h"

class UVerticalBox;
class UTDItemObject;

UCLASS()
class TOPDOWNDEMO_API UTDInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void InitInventoryWidget(class UTDInventoryComponent* Inventory);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> InventoryBox;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TSubclassOf<class UTDItemWidget> ItemWidgetClass;

private:
	TMap<UTDItemObject*, UTDItemWidget*> ItemsMap;
	
	UFUNCTION()
	void OnItemAdded(class UTDItemObject* ItemObject);
	
	UFUNCTION()
	void OnItemRemoved(UTDItemObject* ItemObject);
};
