// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TDAIController.generated.h"

class UTDAIPerceptionComponent;

UCLASS()
class TOPDOWNDEMO_API ATDAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATDAIController();

protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UTDAIPerceptionComponent* AIPerceptionComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
	
private:
	AActor* GetFocusOnActor() const;
};
