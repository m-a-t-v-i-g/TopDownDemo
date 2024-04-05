// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDItemActor.generated.h"

class UTDItemAsset;

UCLASS()
class TOPDOWNDEMO_API ATDItemActor : public AActor
{
	GENERATED_BODY()

public:
	ATDItemActor();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Item")
	TObjectPtr<UTDItemAsset> ItemAsset;
};
