#include "MyGameState.h"
#include "Net/UnrealNetwork.h"

void AMyGameState::AddFoundItem(FName ItemID)
{
    if (HasAuthority() && !FoundItems.Contains(ItemID))
    {
        FoundItems.Add(ItemID);
        OnRep_FoundItems(); // Optional: for the server
    }
}

void AMyGameState::OnRep_FoundItems()
{
    // Notificar a la UI (HUD o Widget)
}

void AMyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMyGameState, FoundItems);
}