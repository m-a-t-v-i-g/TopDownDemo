// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TDItemObject.generated.h"

class UTDItemAsset;
class ATDItemActor;

USTRUCT(BlueprintType)
struct FTDItemParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "Properties")
	float Wear = 0.0f;
};

UCLASS()
class TOPDOWNDEMO_API UTDItemObject : public UObject
{
	GENERATED_BODY()

public:
	void operator=(const ATDItemActor* ItemActor);

	UPROPERTY(EditAnywhere, Category = "Item")
	TSubclassOf<ATDItemActor> ItemClass;
	
protected:
	UPROPERTY(EditAnywhere, Category = "Item")
	TObjectPtr<UTDItemAsset> ItemAsset;

	UPROPERTY(EditAnywhere, Category = "Item")
	FTDItemParams ItemParams;

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE UTDItemAsset* GetItemAsset() const { return ItemAsset; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE FTDItemParams GetItemParams() const { return ItemParams; }
};
