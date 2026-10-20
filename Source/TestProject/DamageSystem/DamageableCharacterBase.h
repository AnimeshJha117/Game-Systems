#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamagableInterface.h"
#include "DamageableCharacterBase.generated.h"

class UDamageSystemComponent;
class USoundBase;

UCLASS()
class TESTPROJECT_API ADamageableCharacterBase : public ACharacter, public IDamagableInterface
{
	GENERATED_BODY()

public:
	ADamageableCharacterBase();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void RespondToDamage(const FDamageInfo& DamageInfo);
	
	UFUNCTION(BlueprintNativeEvent)
	void RespondToHeal(float HealAmount, AActor* Healer);
	
	UFUNCTION(BlueprintNativeEvent)
	void RespondToDeath();
	
	//Sounds
	UPROPERTY(EditDefaultsOnly, Category = "Damage Audio")
	TArray<TObjectPtr<USoundBase>> DamageSounds;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage Audio")
	TArray<TObjectPtr<USoundBase>> HealSounds;
	
	UPROPERTY(EditDefaultsOnly, Category = "Damage Audio")
	TObjectPtr<USoundBase> DeathSound;

public:
	//Damageable Interface Implementation
	virtual float GetMaxHealth_Implementation() override;
	virtual float GetCurrentHealth_Implementation() override;
	virtual bool GetIsDead_Implementation() override;
	virtual void Heal_Implementation(float HealAmount, AActor* Healer) override;
	virtual bool TakeDamage_Implementation(const FDamageInfo& DamageInfo) override;
	
	//Damage System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDamageSystemComponent> DamageSystemComponent;
	
private:
	void PlayFeedbackSound(USoundBase* FeedbackSound) const;
	void PlayRandomSound(const TArray<TObjectPtr<USoundBase>>& Sounds, int32& LastIndex) const;
	int32 LastDamageSoundIndex {INDEX_NONE};
	int32 LastHealSoundIndex {INDEX_NONE};
};