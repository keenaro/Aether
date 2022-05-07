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

	const auto* Camera = Character->GetCamera();
	const auto CameraTransform = Camera->GetComponentTransform();
	const auto CameraForward = Camera->GetForwardVector();
	const FVector Start = Camera->GetComponentLocation();
	const FVector End = Start + CameraForward * Range;
	const FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageGameplayEffect, GetAbilityLevel());

	// Pass the damage to the Damage Execution Calculation through a SetByCaller value on the GameplayEffectSpec
	DamageEffectSpecHandle.Data.Get()->SetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("Data.Damage")), Damage);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto* Projectile = GetWorld()->SpawnActorDeferred<AAetherProjectile>(ProjectileClass, CameraTransform, GetOwningActorFromActorInfo(), Character, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	Projectile->DamageEffectSpecHandle = DamageEffectSpecHandle;
	Projectile->Range = Range;
	Projectile->FinishSpawning(CameraTransform);
}
