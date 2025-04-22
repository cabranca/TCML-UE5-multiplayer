#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

#include "MainCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class UCameraComponent;

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

	UFUNCTION(BlueprintCallable)
	bool IsRunning();

	UFUNCTION(BlueprintCallable)
	bool IsCrouching();

protected:
	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

private:
	// Mesh for first person view (arms seen only by self)
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh1P;

	// Camera component for the player
	UPROPERTY(EditAnywhere)
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RunAction;

	UPROPERTY(EditAnywhere, Category = "Crouching")
	FVector CrouchEyeOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Crouching")
	float CrouchSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Running")
	float RunSpeed = 800.f;

	UPROPERTY(EditAnywhere, Category = "Running")
	float WalkSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Running")
	float StaminaLossRate = 1.f;

	UPROPERTY(EditAnywhere, Category = "Running")
	float StaminaRecoveryRate = 2.f;

	UPROPERTY(EditAnywhere, Category = "Running")
	float StaminExhaustedRecoveryRate = 1.f;

	float CurrentStamina = 100.f;

	const float MaxStamina = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_IsRunning)
	bool bIsRunning = false;

	bool bIsExhausted = false;

	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void OnCrouchTriggered(const FInputActionValue& Value);

	void StartRun(const FInputActionValue& Value);

	void EndRun(const FInputActionValue& Value);

	void UpdateStamina(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerSetRunning(bool bShouldRun);

	UFUNCTION()
	void OnRep_IsRunning();
};
