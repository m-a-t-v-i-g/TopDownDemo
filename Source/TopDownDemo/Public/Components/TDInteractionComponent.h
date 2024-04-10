/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDInteractionComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionDelegate, AActor*);
DECLARE_MULTICAST_DELEGATE(FOnActionDelegate);

UCLASS(Blueprintable, BlueprintType)
class TOPDOWNDEMO_API UTDInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDInteractionComponent();

	/** Обработка клика пользователя. */
	void ProcessInteraction(const FHitResult& HitResult);

	FOnInteractionDelegate OnInteractionDelegate;
	FOnActionDelegate OnActionDelegate;
};
