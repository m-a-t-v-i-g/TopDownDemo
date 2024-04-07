// Fill out your copyright notice in the Description page of Project Settings.

#include "TDCharacter.h"
#include "TDInteractionInterface.h"
#include "TDInventoryComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Equipment/TDEquipmentComponent.h"
#include "Navigation/PathFollowingComponent.h"

FName ATDCharacter::InventoryComponentName = FName("CharacterInventoryComp");
FName ATDCharacter::EquipmentComponentName = FName("CharacterEquipmentComp");

ATDCharacter::ATDCharacter()
{
	InventoryComponentClass = UTDInventoryComponent::StaticClass();
	EquipmentComponentClass = UTDEquipmentComponent::StaticClass();
	
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
	EquipmentComponent = GetComponentByClass<UTDEquipmentComponent>();
	if (!EquipmentComponent)
	{
		EquipmentComponent = NewObject<UTDEquipmentComponent>(this, EquipmentComponentClass, EquipmentComponentName);
		EquipmentComponent->RegisterComponent();
	}
}

void ATDCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	check(EquipmentComponent);
	EquipmentComponent->InitEquipment();
}

void ATDCharacter::TryInteract(AActor* WithActor)
{
	check(WithActor);
	
	TargetToInteract = WithActor;

	/* Расчитаем дистанцию до предмета на плоскости XY, и, если она больше указанной, подходим к предмету на минимальное
	 * расстояние. */
	float Distance = FVector::Dist2D(GetActorLocation(), TargetToInteract->GetActorLocation());
	if (Distance > 100.0f)
	{
		UAIBlueprintHelperLibrary::SimpleMoveToActor(GetController(), TargetToInteract.Get());
		
		FollowingComponent = GetController()->GetComponentByClass<UPathFollowingComponent>();
		if (FollowingComponent.IsValid() && FollowingComponent->GetStatus() == EPathFollowingStatus::Moving)
		{
			/* Биндимся к делегату остановки для последующего интеракшена. */
			StopMovingDelegate = FollowingComponent->OnRequestFinished.AddUObject(this, &ATDCharacter::InteractAfterMoving);
		}
	}
	else
	{
		ProcessInteraction();
	}
}

void ATDCharacter::ProcessInteraction()
{
	ITDInteractionInterface* InteractingActor = Cast<ITDInteractionInterface>(TargetToInteract);
	check(InteractingActor);

	InteractingActor->OnInteraction(this);
	TargetToInteract.Reset();
}

void ATDCharacter::InteractAfterMoving(FAIRequestID RequestID, const FPathFollowingResult& FollowResult)
{
	/* Удаляем связанный делегат и вызываем интеракшн. */
	FollowingComponent->OnRequestFinished.Remove(StopMovingDelegate);
	ProcessInteraction();
}
