// Fill out your copyright notice in the Description page of Project Settings.

#include "TDAIPerceptionComponent.h"
#include "AIController.h"
#include "TDCharacter.h"
#include "TDHealthComponent.h"
#include "Perception/AISense_Sight.h"

UTDAIPerceptionComponent::UTDAIPerceptionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDAIPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTDAIPerceptionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AActor* UTDAIPerceptionComponent::GetClosestEnemy()
{
	TArray<AActor*> PerceiveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
	if (PerceiveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;
	for (const auto PerceiveActor : PerceiveActors)
	{
		if (const auto FoundEnemy = Cast<ATDCharacter>(PerceiveActor))
		{
			const auto HealthComponent = FoundEnemy->FindComponentByClass<UTDHealthComponent>();
			if (HealthComponent && !HealthComponent->IsHealthMinimum())
			{
				const auto CurrentDistance = (PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
				if (CurrentDistance < BestDistance)
				{
					BestDistance = CurrentDistance;
					BestPawn = PerceiveActor;
				}
			}
		}
	}
	return BestPawn;
}
