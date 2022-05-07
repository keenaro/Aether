#include "AetherPlayerState.h"
#include "Aether/AbilitySystem/AetherAbilitySystemComponent.h"
#include "Aether/AbilitySystem/Attributes/AetherAttributeSet.h"

AAetherPlayerState::AAetherPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAetherAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAetherAttributeSet>(TEXT("AttributeSet"));

	// 100 is way too high for a shipping game.
	NetUpdateFrequency = 100.0f;
}

