// Fill out your copyright notice in the Description page of Project Settings.

#include "TDCharacter.h"
#include "TDInventoryComponent.h"

FName ATDCharacter::InventoryComponentName = FName("CharacterInventoryComp");

ATDCharacter::ATDCharacter()
{
	InventoryComponentClass = UTDInventoryComponent::StaticClass();
	PrimaryActorTick.bCanEverTick = true;
}

void ATDCharacter::PreInitializeComponents()
{
	FindOrCreateComponents();
	Super::PreInitializeComponents();
}

void ATDCharacter::FindOrCreateComponents()
{
	/* Проверяем, имеется ли экземпляр компонента у персонажа.
	 * Если компонент валиден (имеется экземпляр блупринта), то перезаписываем поинтер.
	 * Если компонент не валиден, то создаем дефолтный по указанному в <имя компонента>Class классу и регистрируем его у
	 * персонажа. */
	
	InventoryComponent = GetComponentByClass<UTDInventoryComponent>();
	if (!InventoryComponent)
	{
		InventoryComponent = NewObject<UTDInventoryComponent>(this, InventoryComponentClass, InventoryComponentName);
		InventoryComponent->RegisterComponent();
	}
}

void ATDCharacter::ProcessInteraction(AActor* WithActor)
{
	float Distance = FVector::Distance(GetActorLocation(), WithActor->GetActorLocation());
	if (Distance > 25.0f)
	{
		
	}
}
