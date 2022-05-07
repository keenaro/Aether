#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Aether/Aether.h"
#include "AetherGameplayAbility.generated.h"

UCLASS()
class AETHER_API UAetherGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UAetherGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EAetherAbilityInputID AbilityInputID = EAetherAbilityInputID::None;

	// Value to associate an ability with an slot without tying it to an automatically activated input.
	// Passive abilities won't be tied to an input so we need a way to generically associate abilities with slots.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	EAetherAbilityInputID AbilityID = EAetherAbilityInputID::None;

	// Tells an ability to activate immediately when its granted. Used for passive abilities and abilities forced on others.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability")
	bool ActivateAbilityOnGranted = false;

	// If an ability is marked as 'ActivateAbilityOnGranted', activate them immediately when given here
	// Epic's comment: Projects may want to initiate passives or do other "BeginPlay" type of logic here.
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
};
