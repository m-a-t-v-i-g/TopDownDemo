/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "TDMedActor.h"
#include "TDInventoryComponent.h"
#include "Objects/TDMedObject.h"

ATDMedActor::ATDMedActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATDMedActor::OnInteraction(AActor* Interactor)
{
	UTDMedObject* MedObject = Cast<UTDMedObject>(CreateItemObject(UTDMedObject::StaticClass()));
	check(MedObject);

	if (UTDInventoryComponent* FindInventory = Interactor->FindComponentByClass<UTDInventoryComponent>())
	{
		FindInventory->AddItem(MedObject);
		Destroy();
		return;
	}

	MedObject->MarkAsGarbage();
}

UTDItemObject* ATDMedActor::CreateItemObject(UClass* MedObjectClass)
{
	UTDMedObject* CreatedMedObject = nullptr;
	if (MedObjectClass->IsChildOf<UTDMedObject>())
	{
		CreatedMedObject = Cast<UTDMedObject>(Super::CreateItemObject(MedObjectClass));
		*CreatedMedObject = this;
	}
	return CreatedMedObject;
}
