// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objects/TDItemObject.h"
#include "TDMedObject.generated.h"

class ATDMedActor;

UCLASS()
class TOPDOWNDEMO_API UTDMedObject : public UTDItemObject
{
	GENERATED_BODY()
	
public:
	void operator=(const ATDMedActor* MedActor);
};
