#include "MyAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MainCharacter.h"
#include "Kismet/GameplayStatics.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();

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

void AMyAIController::OnNoiseHeard(const FNoiseData& Noise)
{
	if (!GetBlackboardComponent()) return;

	AMainCharacter* HeardCharacter = Cast<AMainCharacter>(Noise.Instigator);
	if (!HeardCharacter) return;

	APawn* AIPawn = GetPawn();
	if (!AIPawn) return;

	float DistanceToNoise = FVector::Dist(Noise.Location, AIPawn->GetActorLocation());

    if (Noise.Loudness >= DistanceToNoise)
	{
		#if !(UE_BUILD_SHIPPING)
		DrawDebugSphere(
		GetWorld(),
		Noise.Location,        
		25.f,               
		12,               
		FColor::Red,        
		false,              
		2.0f             
		);
		#endif
		
		GetBlackboardComponent()->SetValueAsVector("NoiseLocation", Noise.Location);
	}
}

void AMyAIController::RegisterPlayer(AMainCharacter* Player)
{
	Player->OnNoiseMade.AddDynamic(this, &AMyAIController::OnNoiseHeard);
}
