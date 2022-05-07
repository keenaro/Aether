#include "AetherAbilitySystemComponent.h"
#include "Abilities/AetherGameplayAbility.h"
#include "Aether/Character/AetherCharacter.h"

void UAetherAbilitySystemComponent::InitialiseAbilities(AAetherCharacter* Character, TArray<TSubclassOf<UAetherGameplayAbility>>& Abilities)
{
	if (initialisedAbilities) return;

	for (TSubclassOf<UAetherGameplayAbility>& StartupAbility : Abilities)
	{
		GiveAbility(FGameplayAbilitySpec(StartupAbility, Character->GetAbilityLevel(StartupAbility.GetDefaultObject()->AbilityID), static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID), this));
	}

	initialisedAbilities = true;
}

void UAetherAbilitySystemComponent::ReceiveDamage(UAetherAbilitySystemComponent* SourceASC, float UnmitigatedDamage, float MitigatedDamage)
{
	ReceivedDamage.Broadcast(SourceASC, UnmitigatedDamage, MitigatedDamage);
}
