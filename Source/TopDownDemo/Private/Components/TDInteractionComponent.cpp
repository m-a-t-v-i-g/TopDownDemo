/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "TDInteractionComponent.h"
#include "TDInteractionInterface.h"

UTDInteractionComponent::UTDInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDInteractionComponent::ProcessInteraction(const FHitResult& HitResult)
{
	/* Данный метод обрабатывает объект, по которому был произведен щелчок и выстраивает дальнейшие действия в зависимости
	 * от требований. */
	
	AActor* HitActor = HitResult.GetActor();
	if (!IsValid(HitActor)) return;

	if (HitActor->Implements<UTDInteractionInterface>())
	{
		OnInteractionDelegate.Broadcast(HitActor);
	}
	else
	{
		OnActionDelegate.Broadcast();
	}
}
