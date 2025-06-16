#include "BTService_CheckSight.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "MainCharacter.h"

UBTService_CheckSight::UBTService_CheckSight()
{
    bNotifyBecomeRelevant = true;
    bNotifyTick = true;

    NodeName = "Check Line of Sight to Players";
}

void UBTService_CheckSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UBlackboardComponent* BB = OwnerComp.GetBlackboardComponent();
    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* AIPawn = AIController ? AIController->GetPawn() : nullptr;
    if (!AIPawn)
    {
        BB->ClearValue(TargetActorKey.SelectedKeyName);
        return;
    }

    FVector Eyes = AIPawn->GetActorLocation();
    ACharacter* ClosestPlayer = nullptr;
    float MinDistance = SightDistance;

    TArray<AActor*> Players;
    UGameplayStatics::GetAllActorsOfClass(AIPawn->GetWorld(), ACharacter::StaticClass(), Players);

    #if !(UE_BUILD_SHIPPING)
    DrawDebugCone(GetWorld(), AIPawn->GetActorLocation(), AIPawn->GetActorForwardVector(), SightDistance, FMath::DegreesToRadians(FieldOfView * 0.5f), FMath::DegreesToRadians(FieldOfView * 0.5f), 12, FColor::Yellow, false, 0.1f, 0, 1.f);
    #endif

    for (AActor* Actor : Players)
    {
        AMainCharacter* Player = Cast<AMainCharacter>(Actor);
        if (!Player || !Player->IsPlayerControlled()) continue;

        if (Player->IsHiddenInObject()) continue;

        FVector Dir = Player->GetActorLocation() - Eyes;
        float Distance = Dir.Size();
        if (Distance > SightDistance) continue;

        Dir.Normalize();
        float Dot = FVector::DotProduct(AIPawn->GetActorForwardVector(), Dir);
        float CosFOV = FMath::Cos(FMath::DegreesToRadians(FieldOfView / 2));
        if (Dot < CosFOV)  continue;

        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            ClosestPlayer = Player;
        }
    }

    if (ClosestPlayer)
    {
        FHitResult Hit;
        bool bHit = AIPawn->GetWorld()->LineTraceSingleByChannel(Hit, Eyes, ClosestPlayer->GetActorLocation(), ECC_Visibility);

        #if !(UE_BUILD_SHIPPING)
        DrawDebugLine(GetWorld(), Eyes, ClosestPlayer->GetActorLocation(), bHit ? FColor::Green : FColor::Red, false, 0.3f, 0, 1.5f);
        #endif

        if (bHit && Hit.GetActor() == ClosestPlayer)
        {
            BB->SetValueAsObject(TargetActorKey.SelectedKeyName, ClosestPlayer);
            BB->SetValueAsVector(LastKnownLocationKey.SelectedKeyName, ClosestPlayer->GetActorLocation());
        }
        else
        {
            BB->ClearValue(TargetActorKey.SelectedKeyName);
        }
    }
    else
    {
        BB->ClearValue(TargetActorKey.SelectedKeyName);
    }
}