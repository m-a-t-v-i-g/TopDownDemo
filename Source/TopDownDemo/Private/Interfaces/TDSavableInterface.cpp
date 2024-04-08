// Fill out your copyright notice in the Description page of Project Settings.

#include "TDSavableInterface.h"

FTDSaveData ITDSavableInterface::GetFSaveDataRecord_Implementation()
{
	return FTDSaveData();
}

void ITDSavableInterface::LoadFromFSaveDataRecord_Implementation(FTDSaveData Record)
{
}
