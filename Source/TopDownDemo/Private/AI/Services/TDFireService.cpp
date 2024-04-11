// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Services/TDFireService.h"

#include "TDAIPerceptionComponent.h"
#include "TDWeaponComponent.h"
#include "AI/TDAICharacter.h"
#include "AI/TDAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UTDFireService::UTDFireService()
{
	
}

void UTDFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	const auto HasTarget = Blackboard && Blackboard->GetValueAsObject("Enemy");

	if (Controller)
	{
		auto AIController = Cast<ATDAIController>(Controller);
		auto AICharacter = Cast<ATDAICharacter>(AIController->GetPawn());
		const auto PerceptionComponent = AIController->FindComponentByClass<UTDAIPerceptionComponent>();
		const auto WeaponComponent = AICharacter->FindComponentByClass<UTDWeaponComponent>();
		if (PerceptionComponent)
		{
			if (WeaponComponent)
			{
				if (HasTarget)
				{
					auto FoundEnemy = PerceptionComponent->GetClosestEnemy();
					if (FoundEnemy)
					{
						AICharacter->ShotFromWeapon(FoundEnemy->GetActorLocation());
					}
				}
			}
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
