/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TDSaveGame.generated.h"

UCLASS()
class TOPDOWNDEMO_API UTDSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<uint8> ByteData;
};
