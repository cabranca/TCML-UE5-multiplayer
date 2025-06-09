#include "ExitDoor.h"

#include "SimpleAnimatorComponent.h"
#include "SimpleRotatorComponent.h"

// Sets default values
AExitDoor::AExitDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StructureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StructureMesh"));
	StructureMesh->SetupAttachment(RootComponent);

	GateMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GateMesh"));
	GateMesh->SetIsReplicated(true);
	GateMesh->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetIsReplicated(true);
	DoorMesh->SetupAttachment(RootComponent);

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleMesh"));
	HandleMesh->SetIsReplicated(true);
	HandleMesh->SetupAttachment(DoorMesh);

	GateTranslator = CreateDefaultSubobject<USimpleAnimatorComponent>(TEXT("GateTranslator"));
	GateTranslator->TargetMesh = GateMesh;

	DoorRotator = CreateDefaultSubobject<USimpleRotatorComponent>(TEXT("DoorRotator"));
	DoorRotator->TargetMesh = DoorMesh;

	HandleRotator = CreateDefaultSubobject<USimpleRotatorComponent>(TEXT("HandleRotator"));
	HandleRotator->TargetMesh = HandleMesh;
}

void AExitDoor::OpenExitDoor()
{
	GateTranslator->PlayForward();
	DoorRotator->PlayForward();
	HandleRotator->PlayForward();
}
