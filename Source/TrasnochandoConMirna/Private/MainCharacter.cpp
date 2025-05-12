#include "MainCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Statue.h"
#include "Pedestal.h"
#include "PuzzleManager.h"
#include "Blueprint/UserWidget.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AISense_Hearing.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->SetRelativeLocation(FVector(0.0, 0.0, 70.0));
	PlayerCamera->bUsePawnControlRotation = true;
	PlayerCamera->SetIsReplicated(true);

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(PlayerCamera);
	Mesh1P->bOnlyOwnerSee = true;

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
	AddOwnedComponent(PhysicsHandle);
	PhysicsHandle->SetIsReplicated(true);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	FScriptDelegate BeginDelegateSubscriber;
	BeginDelegateSubscriber.BindUFunction(this, "OnCapsuleBeginOverlap");
	GetCapsuleComponent()->OnComponentBeginOverlap.Add(BeginDelegateSubscriber);
	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AStatue::OnSphereBeginOverlap);

	FScriptDelegate EndDelegateSubscriber;
	EndDelegateSubscriber.BindUFunction(this, "OnCapsuleEndOverlap");
	GetCapsuleComponent()->OnComponentEndOverlap.Add(EndDelegateSubscriber);

	//SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AStatue::OnDoorCrossingBegin);

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		if (InteractionWidget)
		{
			InteractionPrompt = CreateWidget<UUserWidget>(PlayerController, InteractionWidget);
			if (InteractionPrompt)
			{
				SetInteractionPrompt();
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not create widget"));
			}
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina(DeltaTime);

	float CrouchInterpTime = FMath::Min(1.f, CrouchSpeed * DeltaTime);
	CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;
	
	if (bGrabbingObject && HasAuthority())
	{
		MulticastUpdateGrabbedObject();
	}

	if (GetVelocity().Length() > 0)
	{
		ProduceNoise();
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!IsLocallyControlled())
	{
		return;
	}

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
	Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
	Input->BindAction(CrouchAction, ETriggerEvent::Started, this, &AMainCharacter::OnCrouchTriggered);
	Input->BindAction(RunAction, ETriggerEvent::Started, this, &AMainCharacter::StartRun);
	Input->BindAction(RunAction, ETriggerEvent::Completed, this, &AMainCharacter::EndRun);
	Input->BindAction(InteractAction, ETriggerEvent::Completed, this, &AMainCharacter::Interact);
}

bool AMainCharacter::IsRunning() const
{
	return bIsRunning;
}

bool AMainCharacter::IsCrouching() const
{
	return bIsCrouched;
}

void AMainCharacter::SetPuzzleManager(APuzzleManager* NewPuzzleManager)
{
	PuzzleManager = NewPuzzleManager;
}

void AMainCharacter::OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0.f)
	{
		return;
	}
	
	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnStartCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight + HalfHeightAdjust;
	PlayerCamera->SetRelativeLocation(FVector(0.0, 0.0, BaseEyeHeight), false);
}

void AMainCharacter::OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust)
{
	if (HalfHeightAdjust == 0.f)
	{
		return;
	}

	float StartBaseEyeHeight = BaseEyeHeight;
	Super::OnEndCrouch(HalfHeightAdjust, ScaledHalfHeightAdjust);
	CrouchEyeOffset.Z += StartBaseEyeHeight - BaseEyeHeight - HalfHeightAdjust;
	PlayerCamera->SetRelativeLocation(FVector(0.0, 0.0, BaseEyeHeight), false);
}

void AMainCharacter::CalcCamera(float DeltaTime, FMinimalViewInfo & OutResult)
{
	if (PlayerCamera)
	{
		PlayerCamera->GetCameraView(DeltaTime, OutResult);
		OutResult.Location += CrouchEyeOffset;
	}
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0, Rotation.Yaw, 0.0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void AMainCharacter::OnCrouchTriggered(const FInputActionValue & Value)
{
	if (bIsCrouched)
	{
		UnCrouch(true);
	}
	else
	{
		Crouch(true);
	}
}

void AMainCharacter::StartRun(const FInputActionValue& Value)
{
	if (!bIsExhausted)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		bIsRunning = true;

		// Notify the server
		ServerSetRunning(bIsRunning);
	}
}

void AMainCharacter::EndRun(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	bIsRunning = false;
	ServerSetRunning(bIsRunning);
}

void AMainCharacter::Interact(const FInputActionValue& Value)
{
	if (!bGrabbingObject)
	{
		FHitResult HitResult;
		bool bHitSucceeded = GetWorld()->LineTraceSingleByChannel(HitResult, PlayerCamera->GetComponentLocation(), PlayerCamera->GetForwardVector() * 500.f + PlayerCamera->GetComponentLocation(), ECC_GameTraceChannel1);

		if (bHitSucceeded)
		{
			AStatue* Statue = Cast<AStatue>(HitResult.GetActor());
			if (Statue)
			{
				DrawDebugLineToLocation(HitResult.Location, FColor::Green);
				GrabObject(HitResult.GetComponent(), Statue);
			}
			else
			{
				DrawDebugLineToLocation(HitResult.Location, FColor::Red);
			}
		}
		else
		{
			DrawDebugLineToLocation(PlayerCamera->GetForwardVector() * 500.f + PlayerCamera->GetComponentLocation(), FColor::Blue);
		}
	}
	else
	{
		FHitResult HitResult;
		bool bHitSucceeded = GetWorld()->LineTraceSingleByChannel(HitResult, PlayerCamera->GetComponentLocation(), PlayerCamera->GetForwardVector() * 500.f + PlayerCamera->GetComponentLocation(), ECC_GameTraceChannel2);

		if (bHitSucceeded)
		{
			APedestal* Pedestal = Cast<APedestal>(HitResult.GetActor());
			if (Pedestal)
			{
				DrawDebugLineToLocation(HitResult.Location, FColor::Green);
				DropObject(HitResult.GetComponent());
			}
			else
			{
				DrawDebugLineToLocation(HitResult.Location, FColor::Red);
			}
		}
	}
}

void AMainCharacter::UpdateStamina(float DeltaTime)
{
	if (CurrentStamina < 0.f)
	{
		CurrentStamina = 0.f;
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		bIsRunning = false;
		bIsExhausted = true;
	}
	else if (CurrentStamina > MaxStamina)
	{
		CurrentStamina = MaxStamina;
		bIsExhausted = false;
	}
	else
	{
		if (bIsRunning)
		{
			CurrentStamina -= StaminaLossRate * DeltaTime;
		}
		else if (bIsExhausted)
		{
			CurrentStamina += StaminExhaustedRecoveryRate * DeltaTime;
		}
		else
		{
			CurrentStamina += StaminaRecoveryRate * DeltaTime;
		}
	}
}

void AMainCharacter::ServerSetRunning_Implementation(bool bInIsRunning)
{
	bIsRunning = bInIsRunning;
	OnRep_IsRunning();
}

void AMainCharacter::OnRep_IsRunning()
{
	GetCharacterMovement()->MaxWalkSpeed = bIsRunning ? RunSpeed : WalkSpeed;
}

void AMainCharacter::DrawDebugLineToLocation(const FVector TargetLocation, FColor Color) const
{
	DrawDebugLine(GetWorld(), PlayerCamera->GetComponentLocation(), TargetLocation, Color, false, 5.f, 0, 0.2f);
}

void AMainCharacter::GrabObject(UPrimitiveComponent* ComponentToGrab, AActor* ObjectToGrab)
{
	PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, PlayerCamera->GetForwardVector() + PlayerCamera->GetComponentLocation(), PlayerCamera->GetComponentRotation());
	bGrabbingObject = true;
	GrabbedObject = ObjectToGrab;
	if (!HasAuthority())
	{
		ServerGrabObject(ComponentToGrab, ObjectToGrab);
	}
}

void AMainCharacter::ServerGrabObject_Implementation(UPrimitiveComponent* ComponentToGrab, AActor* ObjectToGrab)
{
	FRotator Rotator = GetControlRotation();
	//Rotator.Pitch += 1.f;
	FVector Vector = PlayerCamera->GetComponentLocation();
	Vector.Z += 5.f;
	PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, PlayerCamera->GetForwardVector() + Vector, Rotator);
	bGrabbingObject = true;
	GrabbedObject = ObjectToGrab;
}

void AMainCharacter::MulticastUpdateGrabbedObject_Implementation()
{
	FRotator Rotator = GetControlRotation();
	//Rotator.Pitch += 1.f;
	FVector Vector = PlayerCamera->GetComponentLocation();
	Vector.Z += 5.f;
	PhysicsHandle->SetTargetLocationAndRotation(PlayerCamera->GetForwardVector() + Vector, Rotator);
}

void AMainCharacter::DropObject(UPrimitiveComponent* ComponentToDrop)
{
	PhysicsHandle->ReleaseComponent();
	bGrabbingObject = false;
	GrabbedObject->SetActorLocation(ComponentToDrop->GetComponentLocation());
	GrabbedObject->SetActorRotation(FRotator::ZeroRotator);
	GrabbedObject = nullptr;
	if (!HasAuthority())
	{
		ServerDropObject(ComponentToDrop);
	}
	ServerOnStatuePosed();
}

void AMainCharacter::ServerDropObject_Implementation(UPrimitiveComponent* ComponentToDrop)
{
	PhysicsHandle->ReleaseComponent();
	bGrabbingObject = false;
	GrabbedObject->SetActorLocation(ComponentToDrop->GetComponentLocation());
	GrabbedObject->SetActorRotation(FRotator::ZeroRotator);
	GrabbedObject = nullptr;
}

void AMainCharacter::SetInteractionPrompt_Implementation()
{
	if (!InteractionPrompt->AddToPlayerScreen())
	{
		UE_LOG(LogTemp, Error, TEXT("Could not add interaction prompt to player screen"));
	}
	InteractionPrompt->SetVisibility(ESlateVisibility::Collapsed);
}

void AMainCharacter::OnCapsuleBeginOverlap(UCapsuleComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AStatue>(OtherActor) && HasAuthority())
	{
		SetInteractionPromptVisibility(ESlateVisibility::Visible);
		
	}
}

void AMainCharacter::OnCapsuleEndOverlap(UCapsuleComponent * Component, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AStatue>(OtherActor) && HasAuthority())
	{
		SetInteractionPromptVisibility(ESlateVisibility::Hidden);
	}
}

void AMainCharacter::SetInteractionPromptVisibility_Implementation(ESlateVisibility Visibility)
{
	if (InteractionPrompt)
	{
		InteractionPrompt->SetVisibility(Visibility);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Interaction Prompt is null"));
	}
}

void AMainCharacter::ServerOnStatuePosed_Implementation()
{
	if (PuzzleManager)
	{
		PuzzleManager->ServerValidateSolution();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Puzzle Manager set for Main Character"));
	}
}

void AMainCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainCharacter, bIsRunning);
}

void AMainCharacter::ProduceNoise()
{
	float Loudness = WalkingLoudness;
	if (IsRunning())
	{
		Loudness = RunningLoudness;
	}
	else if (IsCrouching())
	{
		Loudness = CrouchingLoudness;
	}
	UAISense_Hearing::ReportNoiseEvent(GetWorld(), GetActorLocation(), Loudness, this, 10.f, NAME_None);
}
