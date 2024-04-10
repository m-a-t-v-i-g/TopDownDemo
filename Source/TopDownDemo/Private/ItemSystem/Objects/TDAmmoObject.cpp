/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "Objects/TDAmmoObject.h"
#include "TDAmmoActor.h"

void UTDAmmoObject::operator=(const ATDAmmoActor* AmmoActor)
{
	ItemAsset = AmmoActor->GetItemAsset();
	ItemParams = AmmoActor->GetItemParams();
	AmmoParams = AmmoActor->GetAmmoParams();
}
