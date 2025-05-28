#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBlackboard.generated.h"

// Task that clears a value in the blackboard.
UCLASS()
class TRASNOCHANDOCONMIRNA_API UBTTask_ClearBlackboard : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
