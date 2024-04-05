// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDInteractionComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionDelegate, AActor*);

UCLASS(Blueprintable, BlueprintType)
class TOPDOWNDEMO_API UTDInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDInteractionComponent();

	void ProcessInteraction(const FHitResult& HitResult);

	FOnInteractionDelegate OnInteractionDelegate;
};
