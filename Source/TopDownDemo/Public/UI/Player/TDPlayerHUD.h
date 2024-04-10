/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TDPlayerHUD.generated.h"

UCLASS()
class TOPDOWNDEMO_API ATDPlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<class UTDPlayerHUDWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TObjectPtr<UTDPlayerHUDWidget> HUDWidget;

	UFUNCTION()
	void OnNewPawn(APawn* OldPawn, APawn* NewPawn);

public:
	UFUNCTION()
	void ToggleInventory();
};
