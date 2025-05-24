#include "SimpleAnimatedObject.h"

#include "SimpleAnimatorComponent.h"

// Sets default values
ASimpleAnimatedObject::ASimpleAnimatedObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);

	Animator = CreateDefaultSubobject<USimpleAnimatorComponent>(TEXT("Animator"));
	Animator->TargetMesh = StaticMesh;
}

void ASimpleAnimatedObject::PlayForward()
{
	Animator->PlayForward();
}

void ASimpleAnimatedObject::PlayReverse()
{
	Animator->PlayReverse();
}

