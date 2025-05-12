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
class UPhysicsHandleComponent;
class APuzzleManager;
class IInteractable;

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

	UFUNCTION() bool IsRunning() const;

	UFUNCTION() bool IsCrouching() const;


	/***SETTERS***/

	UFUNCTION(BlueprintCallable) void SetPuzzleManager(APuzzleManager* NewPuzzleManager);


	/***CROUCHING***/

protected:
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

private:
	UPROPERTY(EditAnywhere, Category = "Crouching") FVector CrouchEyeOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Crouching") float CrouchSpeed = 200.f;


	/***COMPONENTS***/

	// Mesh for first person view (arms seen only by self)
	UPROPERTY(EditAnywhere)	USkeletalMeshComponent* Mesh1P;

	// Camera component for the player
	UPROPERTY(EditAnywhere) UCameraComponent* PlayerCamera;
	
	UPhysicsHandleComponent* PhysicsHandle;
	

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

	bool bGrabbingObject = false;

	AActor* GrabbedObject;

	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> InteractionWidget;
	
	UUserWidget* InteractionPrompt;

	void DrawDebugLineToLocation(const FVector TargetLocation, FColor Color) const;

	void GrabObject(UPrimitiveComponent* ComponentToGrab, AActor* ObjectToGrab);

	UFUNCTION(Server, Reliable) void ServerGrabObject(UPrimitiveComponent* ComponentToGrab, AActor* ObjectToGrab);

	UFUNCTION(NetMulticast, Reliable) void MulticastUpdateGrabbedObject();

	void DropObject(UPrimitiveComponent* ComponentToDrop);

	UFUNCTION(Server, Reliable) void ServerDropObject(UPrimitiveComponent* ComponentToDrop);

	UFUNCTION(Client, Reliable) void SetInteractionPrompt();

	UFUNCTION() void OnCapsuleBeginOverlap(UCapsuleComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION() void OnCapsuleEndOverlap(UCapsuleComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(Client, Reliable) void SetInteractionPromptVisibility(ESlateVisibility Visibility);
	

	/***PUZZLE***/
	
	APuzzleManager* PuzzleManager;
	
	UFUNCTION(Server, Reliable) void ServerOnStatuePosed();

	/***NOISE SYSTEM***/

	UPROPERTY(EditAnywhere, Category = "Noise")
	float CrouchingLoudness = 30.f;

	UPROPERTY(EditAnywhere, Category = "Noise")
	float WalkingLoudness = 150.f;

	UPROPERTY(EditAnywhere, Category = "Noise")
	float RunningLoudness = 300.f;

	void ProduceNoise();
};
