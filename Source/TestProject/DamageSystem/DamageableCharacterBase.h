#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamagableInterface.h"
#include "DamageableCharacterBase.generated.h"

class UDamageSystemComponent;

UCLASS()
class TESTPROJECT_API ADamageableCharacterBase : public ACharacter, public IDamagableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADamageableCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent)
	void RespondToDamage(const FDamageInfo& DamageInfo);
	
	UFUNCTION(BlueprintNativeEvent)
	void RespondToHeal(float HealAmount, AActor* Healer);
	
	UFUNCTION(BlueprintNativeEvent)
	void RespondToDeath();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Damageable Interface Implementation
	virtual float GetMaxHealth_Implementation() override;
	virtual float GetCurrentHealth_Implementation() override;
	virtual bool GetIsDead_Implementation() override;
	virtual void Heal_Implementation(float HealAmount, AActor* Healer) override;
	virtual bool TakeDamage_Implementation(const FDamageInfo& DamageInfo) override;
	
	//Damage System Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UDamageSystemComponent> DamageSystemComponent;
};