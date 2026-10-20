#include "DamageableCharacterBase.h"
#include "DamageSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

ADamageableCharacterBase::ADamageableCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCharacterMovement() -> NavAgentProps.bCanCrouch = true;
	DamageSystemComponent = CreateDefaultSubobject<UDamageSystemComponent>(TEXT("Damage System Component"));
}

// Called when the game starts or when spawned
void ADamageableCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (DamageSystemComponent)
	{
		DamageSystemComponent -> OnDamageTaken.AddDynamic(this, &ADamageableCharacterBase::RespondToDamage);
		DamageSystemComponent -> OnHealRecieved.AddDynamic(this, &ADamageableCharacterBase::RespondToHeal);
		DamageSystemComponent -> OnDeath.AddDynamic(this, &ADamageableCharacterBase::RespondToDeath);
	}
}

void ADamageableCharacterBase::PlayFeedbackSound(USoundBase* FeedbackSound) const
{
	if (FeedbackSound) UGameplayStatics::PlaySoundAtLocation(this, FeedbackSound, GetActorLocation());
}

void ADamageableCharacterBase::PlayRandomSound(const TArray<TObjectPtr<USoundBase>>& Sounds, int32& LastIndex) const
{
	if (Sounds.IsEmpty()) { return; }
	int32 Index = FMath::RandRange(0, Sounds.Num() - 1);
	
	if (Sounds.Num() > 1 && Index == LastIndex) { Index = (Index + 1) % Sounds.Num(); }

	LastIndex = Index;
	PlayFeedbackSound(Sounds[Index]);
}

void ADamageableCharacterBase::RespondToDamage_Implementation(const FDamageInfo& DamageInfo)
{
	if (DamageSystemComponent && DamageSystemComponent -> GetCurrentHealth() > 0.0f)
	{
		PlayRandomSound(DamageSounds, LastDamageSoundIndex);
	}
}

void ADamageableCharacterBase::RespondToHeal_Implementation(float HealAmount, AActor* Healer)
{
	PlayRandomSound(HealSounds, LastHealSoundIndex);
}

void ADamageableCharacterBase::RespondToDeath_Implementation()
{
	PlayFeedbackSound(DeathSound);
	GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh() -> SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh() -> SetSimulatePhysics(true);
}

float ADamageableCharacterBase::GetMaxHealth_Implementation()
{
	if (!DamageSystemComponent) return 0.0f;
	return DamageSystemComponent -> GetMaxHealth();
}

float ADamageableCharacterBase::GetCurrentHealth_Implementation()
{
	if (!DamageSystemComponent) return 0.0f;
	return DamageSystemComponent -> GetCurrentHealth();
}

bool ADamageableCharacterBase::GetIsDead_Implementation()
{
	if (!DamageSystemComponent) return false;
	return DamageSystemComponent -> GetIsDead();
}

void ADamageableCharacterBase::Heal_Implementation(float HealAmount, AActor* Healer)
{
	if (DamageSystemComponent)
	{
		DamageSystemComponent -> HandleIncomingHeal(HealAmount, Healer);
	}
}

bool ADamageableCharacterBase::TakeDamage_Implementation(const FDamageInfo& DamageInfo)
{
	if (!DamageSystemComponent) return false;
	return DamageSystemComponent -> HandleIncomingDamage(DamageInfo);
}