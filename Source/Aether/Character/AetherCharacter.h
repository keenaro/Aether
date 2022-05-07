#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Aether/Aether.h"
#include "AetherCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FInputBool, bool);

class UAetherAbilitySystemComponent;
class UAetherAttributeSet;
class UAetherGameplayAbility;
class UGameplayEffect;
class UCameraComponent;

UCLASS()
class AETHER_API AAetherCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAetherCharacter();

// Getters
public:
	UAetherAbilitySystemComponent* GetAbilitySystemComponent() const { return AbilitySystemComponent.Get(); };
	UCameraComponent* GetCamera() const { return Camera; }

public:
	bool IsAlive() const;
	int GetCharacterLevel() const { return 1; };
	int GetAbilityLevel(EAetherAbilityInputID AbilityID) const { return 1; };

public:
	void SetHealth(float value);

public:
	void PossessedBy(AController* NewController) override;
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

// Rep Functions
protected:
	void OnRep_PlayerState() override;

protected:
	void InitialiseAbilitySystem();
	void InitialiseAttributes();
	void InitialiseAbilities();

	void MoveForward(float Value);
	void MoveRight(float Value);
	void ToggleCrouch(bool doCrouch);

protected:
	TWeakObjectPtr<UAetherAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UAetherAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UAetherGameplayAbility>> Abilities;
};
