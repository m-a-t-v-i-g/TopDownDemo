// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDItemActor.h"
#include "TDMedActor.generated.h"

UCLASS()
class TOPDOWNDEMO_API ATDMedActor : public ATDItemActor
{
	GENERATED_BODY()

public:
	ATDMedActor();

	virtual void OnInteraction(AActor* Interactor) override;
	
	virtual UTDItemObject* CreateItemObject(UClass* MedObjectClass) override;
};
