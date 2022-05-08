#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Aether/Aether.h"
#include "Components/InventoryComponent.h"
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
	UCameraComponent* GetCameraComponent() const { return CameraComponent; }

public:
	bool IsAlive() const;
	int GetCharacterLevel() const { return 1; };
	int GetAbilityLevel(EAetherAbilityInputID AbilityID) const { return 1; };

// Set Functions
public:
	void SetHealth(float value);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SetInventoryItem(UInventoryComponent* inventoryTarget, int index, const FItem newItem);

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

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	TWeakObjectPtr<UAetherAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UAetherGameplayAbility>> Abilities;

// Components
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Replicated, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;

	TWeakObjectPtr<UAetherAbilitySystemComponent> AbilitySystemComponent;

//Exec Functions
public:
	UFUNCTION(Exec)
	void AddItem(FName name, int quantity = 1);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_AddItem(FName name, int quantity);

	UFUNCTION(Exec)
	void ClearInventory();
};
