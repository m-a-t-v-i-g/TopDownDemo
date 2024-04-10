/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "TDFindEnemyService.generated.h"

UCLASS()
class TOPDOWNDEMO_API UTDFindEnemyService : public UBTService
{
	GENERATED_BODY()

public:
	UTDFindEnemyService();

private:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};

