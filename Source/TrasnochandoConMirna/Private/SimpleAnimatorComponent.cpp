#include "SimpleAnimatorComponent.h"

USimpleAnimatorComponent::USimpleAnimatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USimpleAnimatorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (TargetMesh)
	{
		TargetMesh->SetRelativeLocation(bBeginsAtStart? StartLocation : EndLocation);
	}
}


// Called every frame
void USimpleAnimatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bIsAnimating || !TargetMesh)
        return;

    ElapsedTime += DeltaTime;
    float Alpha = FMath::Clamp(ElapsedTime / AnimationDuration, 0.0f, 1.0f);

    FVector NewLocation = FMath::Lerp(RuntimeStartLocation, RuntimeEndLocation, Alpha);

    TargetMesh->SetRelativeLocation(NewLocation);

    if (Alpha >= 1.0f)
    {
        bIsAnimating = false;
    }
}

void USimpleAnimatorComponent::PlayForward()
{
    if (TargetMesh && AnimationDuration > 0)
    {
        RuntimeStartLocation = TargetMesh->GetRelativeLocation();
        RuntimeEndLocation = EndLocation;

        bIsAnimating = true;
        bForward = true;
        ElapsedTime = 0.0f;
    }
}

void USimpleAnimatorComponent::PlayReverse()
{
    if (TargetMesh && AnimationDuration > 0)
    {
        RuntimeStartLocation = TargetMesh->GetRelativeLocation();
        RuntimeEndLocation = StartLocation;

        bIsAnimating = true;
        bForward = false;
        ElapsedTime = 0.0f;
    }
}
