#include "AetherPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Aether/Character/AetherCharacter.h"
#include "Aether/AbilitySystem/AetherAbilitySystemComponent.h"

void AAetherPlayerController::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	if (auto* BaseCharacter = Cast<AAetherCharacter>(P))
	{
		BaseCharacter->GetAbilitySystemComponent()->InitAbilityActorInfo(BaseCharacter, BaseCharacter);
	}
}
