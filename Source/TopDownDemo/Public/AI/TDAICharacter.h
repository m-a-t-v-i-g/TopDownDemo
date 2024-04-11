/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

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

public:	
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
	void ShotFromWeapon(FVector ShotLocation);
};
