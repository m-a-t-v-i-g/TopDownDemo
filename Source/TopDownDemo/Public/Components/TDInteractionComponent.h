﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDInteractionComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWNDEMO_API UTDInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDInteractionComponent();
};
