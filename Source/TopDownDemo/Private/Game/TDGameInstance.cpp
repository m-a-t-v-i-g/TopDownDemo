// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/TDGameInstance.h"
#include "Game/TDSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"

void UTDGameInstance::SaveGameToSlot(FString SlotName)
{
	DataRecords.Empty();
	SaveActors();

	TArray<uint8> BinaryData;
	FMemoryWriter Writer {BinaryData};
	
	FObjectAndNameAsStringProxyArchive Archive {Writer, false};
	Archive.ArIsSaveGame = true;

	Serialize(Archive);

	auto SaveInstance = Cast<UTDSaveGame>(UGameplayStatics::CreateSaveGameObject(UTDSaveGame::StaticClass()));
	SaveInstance->ByteData = BinaryData;
	
	UGameplayStatics::SaveGameToSlot(SaveInstance, SlotName, 0);
}

void UTDGameInstance::LoadFromSlot(FString SlotName)
{
	DataRecords.Empty();
	ClearActors();

	auto LoadGameInstance = Cast<UTDSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));
	check(LoadGameInstance);
	
	TArray<uint8> BinaryData = LoadGameInstance->ByteData;
	FMemoryReader Reader {BinaryData};
	
	FObjectAndNameAsStringProxyArchive Archive {Reader, false};
	Archive.ArIsSaveGame = true;

	Serialize(Archive);

	auto World = GetWorld();
	for (auto i = 0; i < DataRecords.Num(); ++i)
	{
		AActor* RestoredActor = World->SpawnActor<AActor>(DataRecords[i].ActorClass,
		                                                  DataRecords[i].ActorTransform.GetLocation(),
		                                                  DataRecords[i].ActorTransform.GetRotation().Rotator());
		RestoredActor->SetActorLabel(DataRecords[i].ActorName);
		
		if(UKismetSystemLibrary::DoesImplementInterface(RestoredActor, UTDSavableInterface::StaticClass()))
		{
			ITDSavableInterface::Execute_LoadFromFSaveDataRecord(RestoredActor, DataRecords[i]);
		}
	}
	DataRecords.Empty();
}

void UTDGameInstance::SaveActors()
{
	TArray<AActor*> FindActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UTDSavableInterface::StaticClass(), FindActors);
	
	for(const auto Actor : FindActors)
	{
		DataRecords.Add(ITDSavableInterface::Execute_GetFSaveDataRecord(Actor));
	}
}

void UTDGameInstance::ClearActors() const
{
	TArray<AActor*> FindActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UTDSavableInterface::StaticClass(), FindActors);
	
	for(const auto Actor : FindActors)
	{
		Actor->Destroy();
	}
}
