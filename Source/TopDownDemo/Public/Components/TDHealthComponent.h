// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedDelegate, float);
DECLARE_MULTICAST_DELEGATE(FOnOwnerDiedDelegate);

UCLASS(Blueprintable, BlueprintType)
class TOPDOWNDEMO_API UTDHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDHealthComponent();

	void InitHealthComponent(bool bDead);
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float DamageValue) const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetHealth(float HealthValue);

private:
	void CallDeath();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	bool IsHealthMinimum() const;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Health")
	FORCEINLINE float GetHealth() const { return Health; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0"))
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0"))
	float Health = 100.0f;

public:
	FOnHealthChangedDelegate OnHealthChangedDelegate;
	FOnOwnerDiedDelegate OnOwnerDiedDelegate;
};
