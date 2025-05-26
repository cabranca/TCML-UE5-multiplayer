#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIPatrolPathPoint.generated.h"

// Forward declarations
class UArrowComponent;

// Point with a Mesh and Arrow for development to fill the AI patrol path
UCLASS()
class TRASNOCHANDOCONMIRNA_API AAIPatrolPathPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIPatrolPathPoint();

private:
	friend class UBTTask_Patrol;

	UPROPERTY(EditAnywhere)	UStaticMeshComponent* StaticMesh; // Mesh used for development.

	UPROPERTY(EditAnywhere)	UArrowComponent* Arrow; // Indicates the direction where the AI will rotate to.
};
