#include "Earrings.h"

#include "SimpleAnimatorComponent.h"

AEarrings::AEarrings()
{
	Animator = CreateDefaultSubobject<USimpleAnimatorComponent>(TEXT("Animator"));
	Animator->TargetMesh = StaticMesh;

	bCanInteract = false;
	StaticMesh->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
}

void AEarrings::PlayForward()
{
	Animator->PlayForward();
}
