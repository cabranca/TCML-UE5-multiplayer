#include "BTTask_Patrol.h"
#include "MyAIController.h"
#include "Mirna.h"
#include "Components/ArrowComponent.h"

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyAIController* MirnaController = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (MirnaController)
	{
		if (MirnaController != AIController)
		{
			AMirna* Mirna = Cast<AMirna>(MirnaController->GetPawn());
			if (Mirna)
			{
				AIController = MirnaController;
				PatrolType = Mirna->AIBehavior->PatrolType;
				Points = Mirna->AIBehavior->PatrolPoints;
			}
		}
		return MoveToNextPoint();
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UBTTask_Patrol::MoveToNextPoint()
{
	TArray<AAIPatrolPathPoint*> Keys;
	Points.GenerateKeyArray(Keys);
	AAIPatrolPathPoint* CurrentPoint = Keys[CurrentIndex];
	const FVector Destination = CurrentPoint->GetActorLocation();
	EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(Destination, 5.0, false, true);
	
	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnMoveCompleted");
	AIController->ReceiveMoveCompleted.Add(DelegateSubscriber);
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	TArray<AAIPatrolPathPoint*> Keys;
	Points.GenerateKeyArray(Keys);
	AAIPatrolPathPoint* CurrentPoint = Keys[CurrentIndex];

	if (Result == EPathFollowingResult::Success)
	{
		float WaitingTime = Points[CurrentPoint];
		float Maximum = FMath::Max(0.1f, WaitingTime);
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &UBTTask_Patrol::OnEndWaiting, Maximum, false);
		AIController->SetControlRotation(CurrentPoint->Arrow->GetComponentRotation());
	}
}

void UBTTask_Patrol::OnEndWaiting()
{
	CurrentIndex += PathDirection;
	if (CurrentIndex >= 0 && CurrentIndex < Points.Num())
	{
		MoveToNextPoint();
	}
	else
	{
		switch (PatrolType)
		{
		case EPatrolNavigationType::Loop:
			CurrentIndex = 0;
			MoveToNextPoint();
			break;
		case EPatrolNavigationType::Backwards:
			PathDirection *= -1;
			CurrentIndex += PathDirection;
			MoveToNextPoint();
			break;
		case EPatrolNavigationType::None:
			PathDirection *= -1;
			CurrentIndex += PathDirection;
			break;
		}
	}
}
