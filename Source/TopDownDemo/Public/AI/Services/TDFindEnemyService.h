// Fill out your copyright notice in the Description page of Project Settings.

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

