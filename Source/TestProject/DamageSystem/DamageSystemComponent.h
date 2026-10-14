#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageSystemTypes.h"
#include "DamageSystemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken, const FDamageInfo&, DamageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealRecieved, float, HealAmount, AActor*, Healer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewCurrentHealth, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTPROJECT_API UDamageSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDamageSystemComponent();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth {100.0f};
	
private:
	UPROPERTY(VisibleInstanceOnly, Category = "Health")
	float CurrentHealth {0.0f};
	
	UPROPERTY()
	bool IsDead {false};

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "Damage")
	bool HandleIncomingDamage(const FDamageInfo& DamageInfo);
	
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void HandleIncomingHeal(float HealAmount, AActor* Healer);
	
	//Getter Functions
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }
	
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const { return MaxHealth; }
	
	UFUNCTION(BlueprintPure, Category = "Health")
	bool GetIsDead() const { return IsDead; }
	
	
	//Delegates
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDamageTaken OnDamageTaken;
	
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnHealRecieved OnHealRecieved;
	
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnDeath OnDeath;
	
	UPROPERTY(BlueprintAssignable, Category = "Damage Delegates")
	FOnHealthChanged OnHealthChanged;
};