/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "AI/TDAIController.h"
#include "TDAIPerceptionComponent.h"
#include "AI/TDAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

ATDAIController::ATDAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UTDAIPerceptionComponent>("AI Perception Component");
	SetPerceptionComponent(*AIPerceptionComponent);
}

void ATDAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto AICharacter = Cast<ATDAICharacter>(InPawn);
	if (AICharacter)
	{
		RunBehaviorTree(BehaviorTreeAsset);
	}
}

void ATDAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (auto AimActor = GetFocusOnActor())
	{
		SetFocus(AimActor);
	}
}

AActor* ATDAIController::GetFocusOnActor() const
{
	AActor* TargetActor = nullptr;
	if (auto BB = GetBlackboardComponent())
	{
		TargetActor = Cast<AActor>(BB->GetValueAsObject("Enemy"));
	}
	return TargetActor;
}
