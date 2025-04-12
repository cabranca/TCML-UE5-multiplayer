#include "AIPatrolPathPoint.h"
#include "Components/ArrowComponent.h"


AAIPatrolPathPoint::AAIPatrolPathPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(StaticMesh);
}
