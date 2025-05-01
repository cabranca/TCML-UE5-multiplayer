#include "MyAIController.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Navigation/PathFollowingComponent.h"

AMyAIController::AMyAIController()
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception"));
	AddOwnedComponent(PerceptionComponent);
}

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

	FScriptDelegate DelegateSubscriber;
	DelegateSubscriber.BindUFunction(this, "OnSensed");
	GetAIPerceptionComponent()->OnTargetPerceptionUpdated.Add(DelegateSubscriber);

	if (BehaviorTree)
	{
		if (!RunBehaviorTree(BehaviorTree))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to run Behavior Tree"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BehaviorTreeAsset is null"));
	}
}

void AMyAIController::OnSensed(AActor * Origin, FAIStimulus Stimulus)
{
	HandleSightSense(Origin, Stimulus);
	HandleSoundSense(Origin, Stimulus);
}

void AMyAIController::HandleSightSense(AActor * Origin, FAIStimulus Stimulus)
{
	if (Stimulus.Type != UAISense::GetSenseID<UAISense_Sight>())
	{
		return;
	}

	// TODO: check whethere the actor is the character
	if (Stimulus.WasSuccessfullySensed())
	{
		Blackboard->SetValueAsObject(TEXT("TargetActor"), Origin);
	}
	else
	{
		Blackboard->SetValueAsObject(TEXT("TargetActor"), nullptr);
		Blackboard->SetValueAsVector(TEXT("LastKnownLocation"), Stimulus.StimulusLocation);
	}
}

void AMyAIController::HandleSoundSense(AActor * Origin, FAIStimulus Stimulus)
{
	if (Stimulus.Type != UAISense::GetSenseID<UAISense_Hearing>())
	{
		return;
	}

	Blackboard->SetValueAsVector(TEXT("HearingTargetLocation"), Stimulus.StimulusLocation);
}
