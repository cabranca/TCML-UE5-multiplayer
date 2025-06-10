#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleRotatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRASNOCHANDOCONMIRNA_API USimpleRotatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
    USimpleRotatorComponent();

protected:
    virtual void BeginPlay() override;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    /***COMPONENTS***/

    UPROPERTY(EditAnywhere, Category = "Rotation")  UStaticMeshComponent* TargetMesh; // Mesh to rotate.

    UPROPERTY(EditAnywhere, Category = "Rotation") FRotator StartRotation; // Initial rotator of the rotation.

    UPROPERTY(EditAnywhere, Category = "Rotation") FRotator EndRotation; // End rotator of the rotation.


    /***EXPOSED VARIABLES***/

    UPROPERTY(EditAnywhere, Category = "Rotation") float RotationDuration = 1.0f; // Duration of the rotation in seconds.

    UPROPERTY(EditAnywhere, Category = "Animation") bool bBeginsAtStart = true; // Whether the mesh starts at the StartRotation or EndRotation.

    UPROPERTY(EditAnywhere, Category = "Animation") bool bRestartWhenPlay = false; // Whether the animation always starts from the beggining point.


    /***METHODS***/

    void PlayForward(); // Rotates towards the end.

    void PlayReverse(); // Rotates towards the start.


private:
    float ElapsedTime = 0.0f; // Current time since rotation started.
    bool bIsRotating = false; // Whether the rotation is in motion or not.
    bool bForward = true; // Whether the rotation goes from start to end or from end to start.
    FRotator RuntimeStartRotation; // Start Rotator when rotation is called.
    FRotator RuntimeEndRotation; // End Rotator when the rotation is called.
};
