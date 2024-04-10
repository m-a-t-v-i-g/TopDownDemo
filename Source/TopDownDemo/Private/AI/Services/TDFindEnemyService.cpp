// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Services/TDFindEnemyService.h"
#include "AIController.h"
#include "TDAIPerceptionComponent.h"
#include "TDWeaponComponent.h"
#include "AI/TDAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UTDFindEnemyService::UTDFindEnemyService()
{
	NodeName = "Find Enemy Service";
}

void UTDFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (const auto Blackboard = OwnerComp.GetBlackboardComponent())
	{
		const auto AIController = OwnerComp.GetAIOwner();
		if (!AIController) return;
		
		const auto AICharacter = Cast<ATDAICharacter>(AIController->GetPawn());
		if (!AICharacter) return;
		
		const auto PerceptionComponent = AIController->FindComponentByClass<UTDAIPerceptionComponent>();
		const auto WeaponComponent = AICharacter->FindComponentByClass<UTDWeaponComponent>();
		
		if (PerceptionComponent)
		{
			if (WeaponComponent)
			{
				auto FoundEnemy = PerceptionComponent->GetClosestEnemy();
				if (!FoundEnemy)
				{
					AICharacter->ForceStopShooting();
				}
			}
			Blackboard->SetValueAsObject("Enemy", PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
