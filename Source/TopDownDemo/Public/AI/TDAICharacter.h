// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDCharacter.h"
#include "TDAICharacter.generated.h"

UCLASS()
class TOPDOWNDEMO_API ATDAICharacter : public ATDCharacter
{
	GENERATED_BODY()

public:
	ATDAICharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
