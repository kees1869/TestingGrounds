// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "InfiniteTerrainGameMode.h"
#include "AI/Navigation/NavMeshBoundsVolume.h"
#include "engineutils.h"
#include "ActorPool.h"


AInfiniteTerrainGameMode::AInfiniteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

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
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}
