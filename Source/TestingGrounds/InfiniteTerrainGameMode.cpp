// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "engineutils.h"


void AInfiniteTerrainGameMode::PopulateBoundsVolumePool()
{
	// template class
	auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator); // you can think of this (*VolumeIterator )as the content of the VolumeIterator and the
									// content of the VolumeIterator is a an VolumeIterator pointer
		++VolumeIterator;
	}

}

void AInfiniteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *VolumeToAdd)
{
		UE_LOG(LogTemp, Warning, TEXT("Volume found: %s"), *VolumeToAdd->GetName())

}
