/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "Objects/TDWeaponObject.h"
#include "TDWeaponActor.h"

void UTDWeaponObject::operator=(const ATDWeaponActor* WeaponActor)
{
	ItemAsset = WeaponActor->GetItemAsset();
	ItemParams = WeaponActor->GetItemParams();
	WeaponParams = WeaponActor->GetWeaponParams();
}
