// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Tile.generated.h"


USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};


class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 1, int MaxSpawn = 1, float radius = 500, float MinScale = 1, float MaxScale = 1);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void PositionNavMeshBoundsVolume();

	TArray<FSpawnPosition> RandomSpawnPositions(int MinSpawn, int MaxSpawn, float Radius, float MinScale, float MaxScale);

	bool CanSpawnAtLocation(FVector Location, float Radius);
	
	bool FindEmptyLocation(FVector& OutLocation,float Radius);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);

	UActorPool* Pool;

	AActor* NavMeshBoundsVolume;
};
