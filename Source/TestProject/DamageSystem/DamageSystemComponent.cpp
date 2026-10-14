#include "DamageSystemComponent.h"

// Sets default values for this component's properties
UDamageSystemComponent::UDamageSystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UDamageSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

bool UDamageSystemComponent::HandleIncomingDamage(const FDamageInfo& DamageInfo)
{
	if (IsDead || DamageInfo.DamageAmount <= 0.0f) { return false; }
	
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageInfo.DamageAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
	OnDamageTaken.Broadcast(DamageInfo);
	
	
	if (CurrentHealth <= 0.0f)
	{
		IsDead = true;
		OnDeath.Broadcast();
	}
	
	return true;
}

void UDamageSystemComponent::HandleIncomingHeal(float HealAmount, AActor* Healer)
{
	if (IsDead || HealAmount <= 0.0f || CurrentHealth >= MaxHealth) { return; }
	
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
	OnHealRecieved.Broadcast(HealAmount, Healer);
}