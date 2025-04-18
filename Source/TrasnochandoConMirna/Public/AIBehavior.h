#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIPatrolPathPoint.h"

#include "AIBehavior.generated.h"

UENUM()
enum class EPatrolNavigationType { Loop, Backwards, None };

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRASNOCHANDOCONMIRNA_API UAIBehavior : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIBehavior();

private:
	friend class UBTTask_Patrol;

	UPROPERTY(EditAnywhere)
	TMap<AAIPatrolPathPoint*, float> PatrolPoints;

	UPROPERTY(EditAnywhere)
	EPatrolNavigationType PatrolType;
};
