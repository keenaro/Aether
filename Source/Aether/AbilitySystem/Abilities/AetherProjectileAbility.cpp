#include "AetherProjectileAbility.h"
#include "Aether/Character/AetherCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Aether/Projectiles/AetherProjectile.h"

void UAetherProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
		return;
	}

	// Only spawn projectiles on the Server.
	if (GetOwningActorFromActorInfo()->GetLocalRole() != ROLE_Authority) return;

	auto* Character = Cast<AAetherCharacter>(GetAvatarActorFromActorInfo());
	if (!Character)
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}

	const auto* Camera = Character->GetCameraComponent();
	const auto SpawnTransform = FTransform(Character->GetBaseAimRotation(), Camera->GetComponentLocation(), FVector::OneVector);

	FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(Handle, ActorInfo, ActivationInfo, DamageGameplayEffect, GetAbilityLevel());
	// Pass the damage to the Damage Execution Calculation through a SetByCaller value on the GameplayEffectSpec
	DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AAetherProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAetherProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Character, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;
	Projectile->FinishSpawning(SpawnTransform);

	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
}
