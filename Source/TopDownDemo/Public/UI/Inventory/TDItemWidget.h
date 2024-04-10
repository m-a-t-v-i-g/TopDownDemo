/* Top Down shooter demonstration. All rights reserved.
*  Author: matvig */

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
