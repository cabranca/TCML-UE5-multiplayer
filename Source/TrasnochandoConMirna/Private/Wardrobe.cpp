#include "Wardrobe.h"

#include "Camera/CameraComponent.h"

// Sets default values
AWardrobe::AWardrobe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicateMovement(true);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AWardrobe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWardrobe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AWardrobe::ServerInteract_Implementation(AMainCharacter* MainCharacter)
{
	if (MainCharacter != HiddenCharacter)
	{
		if (HiddenCharacter) return;

		HiddenCharacter = MainCharacter;
	}
	else
	{
		HiddenCharacter = nullptr;
	}
	MulticastHidePlayer(MainCharacter);
}

void AWardrobe::MulticastHidePlayer_Implementation(AMainCharacter* MainCharacter)
{
	if (!bPlayerHidden)
	{
		MainCharacter->Hide();
		if (MainCharacter->IsLocallyControlled())
		{
			Cast<APlayerController>(MainCharacter->GetController())->SetViewTargetWithBlend(this, 0.5f);
		}
		bPlayerHidden = true;
	}
	else
	{
		
		if (MainCharacter->IsLocallyControlled())
		{
			Cast<APlayerController>(MainCharacter->GetController())->SetViewTargetWithBlend(MainCharacter, 0.5f);
		}
		MainCharacter->Expose();
		bPlayerHidden = false;
	}
}
