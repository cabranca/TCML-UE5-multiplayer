#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIPatrolPathPoint.h"

#include "AIBehavior.generated.h"

UENUM()
enum class EPatrolNavigationType 
{ 
	Loop, // The patrol starts over when it reaches its last point. 
	Backwards, // The patrol is inverted every time it reaches its last point.
	None // The patrol finishes when it reaches its last point.
};

// Component for a patroling AI.
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRASNOCHANDOCONMIRNA_API UAIBehavior : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIBehavior();

private:
	friend class UBTTask_Patrol;

	UPROPERTY(EditAnywhere) TMap<AAIPatrolPathPoint*, float> PatrolPoints; // Unique Maps of patrol pints for the AI to follow.
	UPROPERTY(EditAnywhere)	EPatrolNavigationType PatrolType; // Behavior of the AI when it reaches its last patrol point.
};
