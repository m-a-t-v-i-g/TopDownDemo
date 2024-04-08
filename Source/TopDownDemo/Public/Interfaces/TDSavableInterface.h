// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDSavableInterface.generated.h"

USTRUCT(BlueprintType)
struct FTDSaveData
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(SaveGame)
	UClass* ActorClass;

	UPROPERTY(SaveGame)
	FString ActorName;

	UPROPERTY(SaveGame)
	FTransform ActorTransform;

	UPROPERTY(SaveGame)
	TArray<uint8> BinaryData;
};

UINTERFACE()
class UTDSavableInterface : public UInterface
{
	GENERATED_BODY()
};

class TOPDOWNDEMO_API ITDSavableInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveLoad")
	FTDSaveData GetFSaveDataRecord();
	virtual FTDSaveData GetFSaveDataRecord_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveLoad")
	void LoadFromFSaveDataRecord(FTDSaveData Record);
	virtual void LoadFromFSaveDataRecord_Implementation(FTDSaveData Record);
};
