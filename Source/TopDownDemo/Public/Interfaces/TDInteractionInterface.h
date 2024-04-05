// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDInteractionInterface.generated.h"

UINTERFACE()
class UTDInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class TOPDOWNDEMO_API ITDInteractionInterface
{
	GENERATED_BODY()

public:
	bool bIsInteractable = true;

	virtual void OnInteraction();
};
