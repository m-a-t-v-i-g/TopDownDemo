/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "TDSavableInterface.h"
#include "Engine/GameInstance.h"
#include "TDGameInstance.generated.h"

UCLASS()
class TOPDOWNDEMO_API UTDGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "SaveLoad")
	void SaveGameToSlot(FString SlotName);

	UFUNCTION(BlueprintCallable, Category = "SaveLoad")
	void LoadFromSlot(FString SlotName);
	
private:
	UPROPERTY(SaveGame)
	TArray<FTDSaveData> DataRecords;

	void SaveActors();
	void ClearActors() const;
};
