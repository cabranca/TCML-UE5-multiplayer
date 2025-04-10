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

	UPROPERTY(EditAnywhere, Category = "Crouch")
	FVector CrouchEyeOffset;

	UPROPERTY(EditAnywhere, Category = "Crouch")
	float CrouchSpeed;

	void Move(const FInputActionValue& Value);
	
	void Look(const FInputActionValue& Value);

	void StartCrouch(const FInputActionValue& Value);

	void EndCrouch(const FInputActionValue& Value);
};
