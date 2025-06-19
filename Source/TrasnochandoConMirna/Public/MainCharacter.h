#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

#include "MainCharacter.generated.h"

// Forward declarations
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UCameraComponent;
class APedestal;
class AInteractableObject;

USTRUCT(BlueprintType)
struct FNoiseData
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FVector Location = FVector::ZeroVector;

    UPROPERTY(BlueprintReadWrite)
    float Loudness = 1.f;

    UPROPERTY(BlueprintReadWrite)
    AActor* Instigator = nullptr;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNoiseMade, const FNoiseData&, Noise);

UCLASS()
class TRASNOCHANDOCONMIRNA_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/***GETTERS***/

	UFUNCTION(BlueprintCallable) bool IsRunning() const;

	UFUNCTION(BlueprintCallable) bool IsCrouching() const;	

	UFUNCTION(BlueprintCallable) bool IsHiddenInObject() const;


	UPROPERTY(BlueprintAssignable) FOnNoiseMade OnNoiseMade;

	/***CROUCHING***/

protected:
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

private:
	UPROPERTY(EditAnywhere, Category = "Crouching") FVector CrouchEyeOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Crouching") float CrouchActionSpeed = 200.f;


	/***COMPONENTS***/

	// Camera component for the player
	UPROPERTY(EditAnywhere) UCameraComponent* PlayerCamera;
	
	UPROPERTY(EditAnywhere) USceneComponent* GrabPivot;

	/***INPUT ACTIONS***/

	UPROPERTY(EditAnywhere, Category = "Input") UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category = "Input") UInputAction* InteractAction;

	/***INPUT CALLBACKS***/

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void OnCrouchTriggered(const FInputActionValue& Value);

	void StartRun(const FInputActionValue& Value);

	void EndRun(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);


	/***MOVEMENT***/

	UPROPERTY(EditAnywhere, Category = "Movement") float RunSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Movement") float WalkSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement") float CrouchSpeed = 150.f;

	UPROPERTY(EditAnywhere, Category = "Movement") float StaminaLossRate = 1.f;

	UPROPERTY(EditAnywhere, Category = "Movement") float StaminaRecoveryRate = 2.f;

	UPROPERTY(EditAnywhere, Category = "Movement") float StaminExhaustedRecoveryRate = 1.f;

	float CurrentStamina = 100.f;

	const float MaxStamina = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_IsRunning)
	bool bIsRunning = false;

	bool bIsExhausted = false;

	void UpdateStamina(float DeltaTime);

	UFUNCTION(Server, Reliable) void ServerSetRunning(bool bShouldRun);

	UFUNCTION()	void OnRep_IsRunning();
	
	
	/***INTERACTION***/

	UPROPERTY(EditAnywhere) UAnimMontage* InteractionMontage;

	UPROPERTY(EditAnywhere, Category = "Interaction") float InteractionRange = 200.f;

	AInteractableObject* TargetActor;

	AInteractableObject* GrabbedActor;

	APedestal* HoveredPedestal;

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> InteractionWidget;
	
	UUserWidget* InteractionPrompt;

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> DiaryWidget;

	UUserWidget* Diary;

	void LookForInteraction();

	void DrawDebugLineToLocation(const FVector TargetLocation, FColor Color) const;

	UFUNCTION(Server, Reliable) void ServerInteract(AInteractableObject* Interactable);

	UFUNCTION(NetMulticast, Reliable) void MulticastPlayInteractMontage();

	UFUNCTION(Server, Reliable) void ServerGrabObject(AInteractableObject* ObjectToGrab);

	void GetPlaceableHint();

	UFUNCTION(Server, Reliable) void ServerDropObject(APedestal* Pedestal, AInteractableObject* Object);

	UFUNCTION(NetMulticast, Reliable) void MulticastDropObject(APedestal* Pedestal, AInteractableObject* Object);

	UFUNCTION(Client, Reliable) void SetInteractionPrompt(UUserWidget* Widget);

	UFUNCTION(Client, Reliable) void SetInteractionPromptVisibility(UUserWidget* Widget, ESlateVisibility Visibility, bool bUIFocused);


	/***NOISE SYSTEM***/

	UPROPERTY(EditAnywhere, Category = "Noise") float CrouchingLoudness = 30.f;

	UPROPERTY(EditAnywhere, Category = "Noise") float WalkingLoudness = 150.f;

	UPROPERTY(EditAnywhere, Category = "Noise") float RunningLoudness = 300.f;

	void ProduceNoise();


	/***HIDING SYSTEM***/

public:
	void Hide();
	UFUNCTION(BlueprintCallable) void Expose();

private:
	bool bIsHidden = false;
};
