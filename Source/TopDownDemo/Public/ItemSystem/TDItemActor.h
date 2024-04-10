/* Top Down shooter demonstration. All rights reserved.
 * Author: matvig */

#pragma once

#include "CoreMinimal.h"
#include "TDInteractionInterface.h"
#include "TDSavableInterface.h"
#include "GameFramework/Actor.h"
#include "Objects/TDItemObject.h"
#include "TDItemActor.generated.h"

class UTDItemAsset;

UCLASS()
class TOPDOWNDEMO_API ATDItemActor : public AActor, public ITDInteractionInterface, public ITDSavableInterface
{
	GENERATED_BODY()

public:
	ATDItemActor();

	virtual void PostInitializeComponents() override;
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void OnInteraction(AActor* Interactor) override;

	virtual void InitItem(UTDItemObject* ItemObject);

	virtual UTDItemObject* CreateItemObject(UClass* ItemObjectClass);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<class USphereComponent> SphereCollision;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TObjectPtr<UStaticMeshComponent> StaticMesh;
	
	UPROPERTY(EditAnywhere, Category = "Item")
	TObjectPtr<UTDItemAsset> ItemAsset;
	
	UPROPERTY(EditInstanceOnly, Category = "Item")
	FTDItemParams ItemParams;

public:
	void SetHandedMode();
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE UTDItemAsset* GetItemAsset() const { return ItemAsset; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Item")
	FORCEINLINE FTDItemParams GetItemParams() const { return ItemParams; }
};
