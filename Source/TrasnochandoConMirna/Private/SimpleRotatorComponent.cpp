#include "SimpleRotatorComponent.h"

USimpleRotatorComponent::USimpleRotatorComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USimpleRotatorComponent::BeginPlay()
{
    Super::BeginPlay();

    if (TargetMesh)
    {
        TargetMesh->SetRelativeRotation(bBeginsAtStart ? StartRotation : EndRotation);
    }
}

void USimpleRotatorComponent::PlayForward()
{
    if (TargetMesh && RotationDuration > 0)
    {
        RuntimeStartRotation = bRestartWhenPlay? StartRotation : TargetMesh->GetRelativeRotation();
        RuntimeEndRotation = EndRotation;

        bIsRotating = true;
        bForward = true;
        ElapsedTime = 0.0f;
    }
}

void USimpleRotatorComponent::PlayReverse()
{
    if (TargetMesh && RotationDuration > 0)
    {
        RuntimeStartRotation = bRestartWhenPlay? EndRotation : TargetMesh->GetRelativeRotation();
        RuntimeEndRotation = StartRotation;

        bIsRotating = true;
        bForward = false;
        ElapsedTime = 0.0f;
    }
}

void USimpleRotatorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bIsRotating || !TargetMesh)
        return;

    ElapsedTime += DeltaTime;
    float Alpha = FMath::Clamp(ElapsedTime / RotationDuration, 0.0f, 1.0f);

    FRotator NewRotation = FMath::Lerp(RuntimeStartRotation, RuntimeEndRotation, Alpha);

    TargetMesh->SetRelativeRotation(NewRotation);

    if (Alpha >= 1.0f)
    {
        bIsRotating = false;
    }
}
