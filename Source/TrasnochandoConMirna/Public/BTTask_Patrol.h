#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIBehavior.h"
#include "Navigation/PathFollowingComponent.h"

#include "BTTask_Patrol.generated.h"

// Forward declarations.
class AMyAIController;

// Task for the AI that moves the pawn to each patrol point.
UCLASS()
class TRASNOCHANDOCONMIRNA_API UBTTask_Patrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	EBTNodeResult::Type MoveToNextPoint(); // Select the next patrol moint and move the AI towards it.

	UFUNCTION() void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result); // Callback for when the AI Move is completed.
	
	void OnEndWaiting(); // Callback for when the AI must move to the next point (if exists).

	AMyAIController* AIController; // Class that controls the AI.
	EPatrolNavigationType PatrolType; // Type of patrol for this AI task.
	TMap<AAIPatrolPathPoint*, float> Points; // Collection of patrol points for the AI to fulfill.
	uint8 CurrentIndex = 0; // Index to itarate through the patrol points.
	uint8 PathDirection = 1; // Indicates if the iteration goes forwards or backwards.

	FTimerHandle SpawnTimerHandle; // Helper class for the Timer that calls OnEndWaiting.
};
