#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

UCLASS()
class AMyGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    // Replicated array of found items
    UPROPERTY(ReplicatedUsing=OnRep_FoundItems) TArray<FName> FoundItems;

    // Adds a found item if it’s not already in the list
    UFUNCTION(BlueprintCallable) void AddFoundItem(FName ItemID);

protected:
    UFUNCTION() void OnRep_FoundItems();

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};