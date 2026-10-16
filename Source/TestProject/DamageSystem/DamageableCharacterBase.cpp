#include "DamageableCharacterBase.h"
#include "DamageSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

ADamageableCharacterBase::ADamageableCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
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

void ADamageableCharacterBase::RespondToDamage_Implementation(const FDamageInfo& DamageInfo)
{
	if (DamageSystemComponent && DamageSystemComponent -> GetCurrentHealth() > 0.0f)
	{
		PlayFeedbackSound(DamageSound);
	}
}

void ADamageableCharacterBase::RespondToHeal_Implementation(float HealAmount, AActor* Healer)
{
	PlayFeedbackSound(HealSound);
}

void ADamageableCharacterBase::RespondToDeath_Implementation()
{
	PlayFeedbackSound(DeathSound);
	GetCapsuleComponent() -> SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh() -> SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh() -> SetSimulatePhysics(true);
}

// Called every frame
void ADamageableCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADamageableCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
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