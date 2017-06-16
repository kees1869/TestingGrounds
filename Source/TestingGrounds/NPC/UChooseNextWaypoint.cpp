// Fill out your copyright notice in the Description page of Project Settings.

#include "TestingGrounds.h"
#include "UChooseNextWaypoint.h"
#include "AIController.h"
#include "PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	// get the patrol route
	auto AIController = OwnerComp.GetAIOwner();
	auto ControlledPawn = AIController->GetPawn();
	auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	auto GuardName = ControlledPawn->GetName();

	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	// warn about empty patrol routes
	auto PatrolPoints = PatrolRoute->GetPatrolPoints();
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Guard: %s has an empty Patrol Route! (no Patrol Points found)"), *GuardName)
		return EBTNodeResult::Failed;
	}

	// set next patrol point
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	// cycle the index
	auto NextIndex = (Index + 1) % PatrolPoints.Num(); // .Num() gets the number of elements in the array
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);

	return EBTNodeResult::Succeeded;
}
