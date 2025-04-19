// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	void OnStartCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void OnEndCrouch(float HalfHeightAdjust, float ScaledHalfHeightAdjust) override;
	void CalcCamera(float DeltaTime, struct FMinimalViewInfo& OutResult) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

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

	UPROPERTY(EditAnywhere, Category = "Crouch")
	FVector CrouchEyeOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Crouch")
	float CrouchSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Run")
	float RunSpeed = 800.f;

	UPROPERTY(EditAnywhere, Category = "Run")
	float WalkSpeed = 500.f;

	UPROPERTY(EditAnywhere, Category = "Run")
	float FatigueRate = 1.f;

	bool bIsRunning = false;

	float CurrentStamina = 100.f;

	const float MaxStamina = 100.f;

	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void OnCrouchTriggered(const FInputActionValue& Value);

	void StartRun(const FInputActionValue& Value);

	void EndRun(const FInputActionValue& Value);
};
