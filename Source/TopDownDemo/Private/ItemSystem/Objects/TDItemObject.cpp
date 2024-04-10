/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "Objects/TDItemObject.h"
#include "TDItemActor.h"

void UTDItemObject::operator=(const ATDItemActor* ItemActor)
{
	ItemAsset = ItemActor->GetItemAsset();
	ItemParams = ItemActor->GetItemParams();
	ItemClass = ItemActor->GetClass();
}
