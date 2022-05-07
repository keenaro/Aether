#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Aether/AbilitySystem/AetherAbilitySystemComponent.h"
#include "AetherAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS(BlueprintType)
class AETHER_API UAetherAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	ATTRIBUTE_ACCESSORS(UAetherAttributeSet, Health)
	ATTRIBUTE_ACCESSORS(UAetherAttributeSet, MaxHealth)
	ATTRIBUTE_ACCESSORS(UAetherAttributeSet, Damage)
	ATTRIBUTE_ACCESSORS(UAetherAttributeSet, Armor)

public:
	void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue);
	void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

// Rep Functions
protected:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Damage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldValue);

public:
	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health, meta=(AllowPrivateAccess=true))
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, Category = "MaxHealth", ReplicatedUsing = OnRep_MaxHealth, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_Damage, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Damage;

	UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_Armor, meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Armor;

};
