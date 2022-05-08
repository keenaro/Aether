#include "AetherCharacter.h"
#include "Aether/AbilitySystem/AetherAbilitySystemComponent.h"
#include "Aether/AbilitySystem/Attributes/AetherAttributeSet.h"
#include "Aether/AbilitySystem/Abilities/AetherGameplayAbility.h"
#include "Aether/Player/AetherPlayerState.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

AAetherCharacter::AAetherCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetWorldLocation(FVector(0, 0, 70));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;
	GetMesh()->SetOwnerNoSee(true);
	Cast<UCharacterMovementComponent>(GetMovementComponent())->NavAgentProps.bCanCrouch = true;

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
}

void AAetherCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);

	//Bind Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AAetherCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAetherCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Horizontal", this, &AAetherCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Vertical", this, &AAetherCharacter::AddControllerPitchInput);

	//Bind Actions
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AAetherCharacter::Jump);
	PlayerInputComponent->BindAction<FInputBool>("Crouch", IE_Pressed, this, &AAetherCharacter::ToggleCrouch, true);
	PlayerInputComponent->BindAction<FInputBool>("Crouch", IE_Released, this, &AAetherCharacter::ToggleCrouch, false);
}

void AAetherCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AAetherCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector(), value);
}

void AAetherCharacter::ToggleCrouch(bool doCrouch)
{
	if (doCrouch) Crouch();
	else UnCrouch();
}

void AAetherCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAetherCharacter, InventoryComponent);
}

bool AAetherCharacter::IsAlive() const
{
	return AttributeSet.IsValid() && AttributeSet->GetHealth() > 0.f;
}

void AAetherCharacter::SetHealth(float value)
{
	if(AttributeSet.IsValid())
	{
		AttributeSet->SetHealth(value);
	}
}

void AAetherCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitialiseAbilitySystem();

	SetOwner(NewController);
}

void AAetherCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitialiseAbilitySystem();
}

void AAetherCharacter::InitialiseAbilitySystem()
{
	if (auto* PS = GetPlayerState<AAetherPlayerState>())
	{
		AbilitySystemComponent = PS->GetAbilitySystemComponent();
		AbilitySystemComponent->InitAbilityActorInfo(PS, this);
		AttributeSet = PS->GetAttributeSet();
		InitialiseAttributes();
		SetHealth(AttributeSet->GetMaxHealth());
	}
}

void AAetherCharacter::InitialiseAttributes()
{
	if (!AbilitySystemComponent.IsValid())
	{
		return;
	}

	if (!DefaultAttributes)
	{
		UE_LOG(LogTemp, Error, TEXT("Missing DefaultAttributes for %s. Please fill in the character's Blueprint."), *GetName());
		return;
	}

	// Can run on Server and Client
	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, GetCharacterLevel(), EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent.Get());
	}
}

void AAetherCharacter::InitialiseAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !AbilitySystemComponent.IsValid()) return;

	AbilitySystemComponent->InitialiseAbilities(this, Abilities);
}

void AAetherCharacter::SetInventoryItem_Implementation(UInventoryComponent* inventoryTarget, int index, const FItem newItem)
{
	inventoryTarget->SetInventoryItem(index, newItem);
}

void AAetherCharacter::AddItem(FName name, int quantity)
{
	if (IsNetMode(NM_ListenServer))
	{
		FItem item(name, quantity);
		InventoryComponent->AddItem(item);
	}
	else Server_AddItem(name, quantity);
}

void AAetherCharacter::Server_AddItem_Implementation(FName name, int quantity)
{
	AddItem(name, quantity);
}

void AAetherCharacter::ClearInventory()
{
	InventoryComponent->ClearInventory();
}

