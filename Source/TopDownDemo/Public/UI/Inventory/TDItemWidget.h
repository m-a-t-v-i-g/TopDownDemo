// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDItemWidget.generated.h"

class UTextBlock;

UCLASS()
class TOPDOWNDEMO_API UTDItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextItemName;

	TWeakObjectPtr<class UTDItemObject> ItemObject;
	
protected:
	UFUNCTION()
	FText GetItemName();
};
