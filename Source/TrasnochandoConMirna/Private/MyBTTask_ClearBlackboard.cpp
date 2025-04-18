#include "MyBTTask_ClearBlackboard.h"

#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UMyBTTask_ClearBlackboard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* MirnaController = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (MirnaController)
	{
		MirnaController->GetBlackboardComponent()->ClearValue(BlackboardKey.SelectedKeyName);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
