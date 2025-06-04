#include "MainCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Statue.h"
#include "Pedestal.h"
#include "Blueprint/UserWidget.h"
#include "Perception/AISense_Hearing.h"
#include "Components/CapsuleComponent.h"
#include "Diary.h"
#include "Kismet/GameplayStatics.h"
#include "GameplayGameMode.h"

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

	GrabPivot = CreateDefaultSubobject<USceneComponent>(TEXT("GrabPivot"));
	GrabPivot->SetupAttachment(PlayerCamera);
	GrabPivot->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
	GrabPivot->SetUsingAbsoluteLocation(false);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = CrouchSpeed;

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
				SetInteractionPrompt(InteractionPrompt);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not create InteractionPrompt"));
			}
		}

		if (DiaryWidget)
		{
			Diary = CreateWidget<UUserWidget>(PlayerController, DiaryWidget);
			if (Diary)
			{
				SetInteractionPrompt(Diary);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Could not create Diary"));
			}
		}
	}
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateStamina(DeltaTime);

	float CrouchInterpTime = FMath::Min(1.f, CrouchActionSpeed * DeltaTime);
	CrouchEyeOffset = (1.f - CrouchInterpTime) * CrouchEyeOffset;

	if (GetVelocity().Length() > 0)
	{
		ProduceNoise(); //TODO: check if this can be called only on Server
	}

	if (IsLocallyControlled())
	{
		if (GrabbedActor)
		{
			GetPlaceableHint();
		}
		else
		{
			LookForInteraction();
		}
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

bool AMainCharacter::IsHiddenInObject() const
{
	return bIsHidden;
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
	if (bIsHidden) return;

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
	if (bIsHidden) return;

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
	if (!GrabbedActor)
	{
		if (TargetActor)
		{
			if (IInteractable::Execute_CanGrab(TargetActor))
			{
				SetInteractionPromptVisibility(InteractionPrompt, ESlateVisibility::Collapsed, false);
				ServerGrabObject(TargetActor);
				GrabbedActor = TargetActor;
			}
			ServerInteract(TargetActor);

			// TODO: Find another way to do this.
			if (Cast<ADiary>(TargetActor))
			{
				SetInteractionPromptVisibility(Diary, ESlateVisibility::Visible, true);
			}
		}
	}
	else if (HoveredPedestal)
	{
		ServerDropObject(HoveredPedestal, TargetActor);
		GrabbedActor = nullptr;
		HoveredPedestal = nullptr;
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

void AMainCharacter::LookForInteraction()
{
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + PlayerCamera->GetForwardVector() * InteractionRange;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (GrabbedActor)
	{
		Params.AddIgnoredActor(GrabbedActor);
	}

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel1, Params))
	{
		AInteractableObject* Interactable = Cast<AInteractableObject>(Hit.GetActor());
		if (Interactable && Interactable != TargetActor)
		{
			SetInteractionPromptVisibility(InteractionPrompt, ESlateVisibility::Visible, false);
			if (TargetActor)
			{
				IInteractable::Execute_Highlight(TargetActor, false);
			}
			TargetActor = Interactable;
			IInteractable::Execute_Highlight(TargetActor, true);
		}
		else if (!Interactable && TargetActor)
		{
			SetInteractionPromptVisibility(InteractionPrompt, ESlateVisibility::Collapsed, false);
			IInteractable::Execute_Highlight(TargetActor, false);
			TargetActor = nullptr;
		}
	}
	else if (TargetActor)
	{
			SetInteractionPromptVisibility(InteractionPrompt, ESlateVisibility::Collapsed, false);
			IInteractable::Execute_Highlight(TargetActor, false);
			TargetActor = nullptr;
	}
}

void AMainCharacter::DrawDebugLineToLocation(const FVector TargetLocation, FColor Color) const
{
	DrawDebugLine(GetWorld(), PlayerCamera->GetComponentLocation(), TargetLocation, Color, false, 5.f, 0, 0.2f);
}

void AMainCharacter::ServerInteract_Implementation(AInteractableObject* Object)
{
	if (IInteractable::Execute_IsLootable(Object))
	{
		AGameplayGameMode* GameMode = Cast<AGameplayGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->SetLootedObject(Object->Tag);
		}
	}
	Object->ServerInteract(this);
	MulticastPlayInteractMontage();
}

void AMainCharacter::MulticastPlayInteractMontage_Implementation()
{
	if (InteractionMontage)
	{
		PlayAnimMontage(InteractionMontage);
	}
}

void AMainCharacter::ServerGrabObject_Implementation(AInteractableObject* ObjectToGrab)
{
	UStaticMeshComponent* ObjectMesh = IInteractable::Execute_GetMeshToGrab(ObjectToGrab);
	ObjectMesh->SetSimulatePhysics(false);
	ObjectMesh->AttachToComponent(GrabPivot, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AMainCharacter::GetPlaceableHint()
{
	FVector Start = PlayerCamera->GetComponentLocation();
	FVector End = Start + PlayerCamera->GetForwardVector() * InteractionRange;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel2, Params))
	{
		APedestal* Pedestal = Cast<APedestal>(Hit.GetActor());

		if (Pedestal && Pedestal != HoveredPedestal)
		{
			if (HoveredPedestal)
			{
				HoveredPedestal->HideGhost();
			}

			HoveredPedestal = Pedestal;
			HoveredPedestal->ShowGhost(IInteractable::Execute_GetMeshToGrab(GrabbedActor)->GetStaticMesh());
		}
		else if (!Pedestal && HoveredPedestal)
		{
			HoveredPedestal->HideGhost();
			HoveredPedestal = nullptr;
		}
	}
	else if (HoveredPedestal)
	{
		HoveredPedestal->HideGhost();
		HoveredPedestal = nullptr;
	}
}

void AMainCharacter::ServerDropObject_Implementation(APedestal* Pedestal, AInteractableObject* Object)
{
	UStaticMeshComponent* GrabbedMesh = IInteractable::Execute_GetMeshToGrab(Object);
	GrabbedMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	GrabbedMesh->SetSimulatePhysics(true);
	MulticastDropObject(Pedestal, Object);
}

void AMainCharacter::MulticastDropObject_Implementation(APedestal* Pedestal, AInteractableObject* Object)
{
	Pedestal->PlaceObject(Object);
}

void AMainCharacter::SetInteractionPrompt_Implementation(UUserWidget* Widget)
{
	if (!Widget->AddToPlayerScreen())
	{
		UE_LOG(LogTemp, Error, TEXT("Could not add widget to player screen"));
	}
	Widget->SetVisibility(ESlateVisibility::Collapsed);
}

void AMainCharacter::SetInteractionPromptVisibility_Implementation(UUserWidget* Widget, ESlateVisibility Visibility, bool bUIFocused)
{
	if (Widget)
	{
		Widget->SetVisibility(Visibility);
		if (bUIFocused)
		{
			FInputModeGameAndUI InputMode;
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			InputMode.SetHideCursorDuringCapture(false);
			InputMode.SetWidgetToFocus(Widget->TakeWidget());
			APlayerController* PlayerController = Cast<APlayerController>(Controller);
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Widget is null"));
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

void AMainCharacter::Hide()
{
	if (bIsHidden) return;

	GetMesh()->SetVisibility(false);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bIsHidden = true;
}

void AMainCharacter::Expose()
{
	if (!bIsHidden) return;

	GetMesh()->SetVisibility(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bIsHidden = false;
}
