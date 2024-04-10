/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDItemAsset.generated.h"

UCLASS()
class TOPDOWNDEMO_API UTDItemAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FText Description;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSoftObjectPtr<UStaticMesh> StaticMesh;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE FText GetItemName() const { return Name; }
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE UStaticMesh* GetStaticMesh() const { return StaticMesh.Get(); }
};
