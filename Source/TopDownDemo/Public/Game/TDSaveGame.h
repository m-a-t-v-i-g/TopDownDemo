// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TDSaveGame.generated.h"

UCLASS()
class TOPDOWNDEMO_API UTDSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<uint8> ByteData;
};
