#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UDamageSystemComponent;

UCLASS(Abstract)
class TESTPROJECT_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Health Bar")
	void SetWatchedComponent(UDamageSystemComponent* NewComponent);
	
protected:
	virtual void NativeDestruct() override;
	
	UFUNCTION()
	void HandleHealthChanged(float NewCurrentHealth, float NewMaxHealth);

	void UpdateDisplay(float Current, float Max);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Health Bar")
	void OnHealthUpdated(float Current, float Max);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthBar;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> HealthText;

private:
	TWeakObjectPtr<UDamageSystemComponent> WatchedComponent;
};