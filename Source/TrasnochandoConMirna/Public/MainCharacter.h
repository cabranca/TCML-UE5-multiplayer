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


	/***SETTERS***/

	void SetVisibility(bool bIsVisible);


	/***CROUCHING***/

protected:
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

private:
	UPROPERTY(EditAnywhere, Category = "Crouching") FVector CrouchEyeOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Crouching") float CrouchSpeed = 200.f;


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


	/***RUNNING***/

	UPROPERTY(EditAnywhere, Category = "Running") float RunSpeed = 800.f;

	UPROPERTY(EditAnywhere, Category = "Running") float WalkSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Running") float StaminaLossRate = 1.f;

	UPROPERTY(EditAnywhere, Category = "Running") float StaminaRecoveryRate = 2.f;

	UPROPERTY(EditAnywhere, Category = "Running") float StaminExhaustedRecoveryRate = 1.f;

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

	UStaticMeshComponent* GrabbedMesh;

	APedestal* HoveredPedestal;

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> InteractionWidget;
	
	UUserWidget* InteractionPrompt;

	void LookForInteraction();

	void DrawDebugLineToLocation(const FVector TargetLocation, FColor Color) const;

	UFUNCTION(Server, Reliable) void ServerInteract(AInteractableObject* Interactable);

	UFUNCTION(NetMulticast, Reliable) void MulticastPlayInteractMontage();

	UFUNCTION(Server, Reliable) void ServerGrabObject(UStaticMeshComponent* ObjectToGrab);

	UFUNCTION(NetMulticast, Reliable) void MulticastGrabObject(UStaticMeshComponent* ObjectToGrab);

	void GetPlaceableHint();

	UFUNCTION(Server, Reliable) void ServerDropObject(APedestal* Pedestal, AInteractableObject* Object);

	UFUNCTION(NetMulticast, Reliable) void MulticastDropObject(APedestal* Pedestal, AInteractableObject* Object);

	UFUNCTION(Client, Reliable) void SetInteractionPrompt();

	UFUNCTION(Client, Reliable) void SetInteractionPromptVisibility(ESlateVisibility Visibility);


	/***NOISE SYSTEM***/

	UPROPERTY(EditAnywhere, Category = "Noise")
	float CrouchingLoudness = 30.f;

	UPROPERTY(EditAnywhere, Category = "Noise")
	float WalkingLoudness = 150.f;

	UPROPERTY(EditAnywhere, Category = "Noise")
	float RunningLoudness = 300.f;

	void ProduceNoise();
};
