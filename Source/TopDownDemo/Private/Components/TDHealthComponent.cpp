// Fill out your copyright notice in the Description page of Project Settings.

#include "TDHealthComponent.h"

UTDHealthComponent::UTDHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDHealthComponent::InitHealthComponent(bool bDead)
{
	OnHealthChangedDelegate.AddUObject(this, &UTDHealthComponent::SetHealth);
	
	if (bDead || Health <= 0.0f)
	{
		OnHealthChangedDelegate.Broadcast(0.0f);
		return;
	}
	
	if (Health > MaxHealth)
	{
		MaxHealth = Health;
	}
}

void UTDHealthComponent::TakeDamage(float DamageValue) const
{
	if (IsHealthMinimum() || DamageValue <= 0.0f)
	{
		return;
	}
	float UpdateHealth = FMath::Clamp(Health - DamageValue, 0.0f, MaxHealth);
	OnHealthChangedDelegate.Broadcast(UpdateHealth);
}

void UTDHealthComponent::RestoreHealth(float Value)
{
	if (IsHealthMinimum() || Value <= 0.0f)
	{
		return;
	}
	float UpdateHealth = FMath::Clamp(Health + Value, 0.0f, MaxHealth);
	OnHealthChangedDelegate.Broadcast(UpdateHealth);
}

void UTDHealthComponent::SetHealth(float HealthValue)
{
	Health = HealthValue;
	if (IsHealthMinimum())
	{
		CallDeath();
	}
}

void UTDHealthComponent::CallDeath()
{
	OnOwnerDiedDelegate.Broadcast();
}

bool UTDHealthComponent::IsHealthMinimum() const
{
	return Health <= 0.0f;
}

bool UTDHealthComponent::IsHealthMaximum() const
{
	return Health == MaxHealth;
}
