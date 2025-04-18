#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIBehavior.h"
#include "Navigation/PathFollowingComponent.h"

#include "BTTask_Patrol.generated.h"

class AMyAIController;
/**
 * 
 */
UCLASS()
class TRASNOCHANDOCONMIRNA_API UBTTask_Patrol : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
	EBTNodeResult::Type MoveToNextPoint();

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	void OnEndWaiting();

	AMyAIController* AIController;
	EPatrolNavigationType PatrolType;
	TMap<AAIPatrolPathPoint*, float> Points;
	uint8 CurrentIndex = 0;
	uint8 PathDirection = 1;

	// Helper for timing
	FTimerHandle SpawnTimerHandle;
};
