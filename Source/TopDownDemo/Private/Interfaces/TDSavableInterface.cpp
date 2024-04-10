/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#include "TDSavableInterface.h"

FTDSaveData ITDSavableInterface::GetFSaveDataRecord_Implementation()
{
	return FTDSaveData();
}

void ITDSavableInterface::LoadFromFSaveDataRecord_Implementation(FTDSaveData Record)
{
}
