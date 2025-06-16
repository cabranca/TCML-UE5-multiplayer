#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckSight.generated.h"


UCLASS()
class TRASNOCHANDOCONMIRNA_API UBTService_CheckSight : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_CheckSight();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetActorKey;

	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector LastKnownLocationKey;

    UPROPERTY(EditAnywhere, Category = "Sight")
    float SightDistance = 1500.f;

    UPROPERTY(EditAnywhere, Category = "Sight")
    float FieldOfView = 90.f;
};
