// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/TDAICharacter.h"

ATDAICharacter::ATDAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATDAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATDAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

