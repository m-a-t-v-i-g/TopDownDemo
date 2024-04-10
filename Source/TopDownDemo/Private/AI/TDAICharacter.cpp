/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

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

