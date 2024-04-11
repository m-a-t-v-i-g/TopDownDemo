/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "AI/TDAICharacter.h"

#include "TDWeaponComponent.h"

ATDAICharacter::ATDAICharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATDAICharacter::BeginPlay()
{
	Super::BeginPlay();

	WeaponComponent->UpdateHandedWeapon(2);
}

void ATDAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATDAICharacter::ShotFromWeapon(FVector ShotLocation)
{
	if (IsArmed())
	{
		WeaponComponent->StartShot(ShotLocation);
	}
}

