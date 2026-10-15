#include "HealthBarWidget.h"
#include "../DamageSystem/DamageSystemComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBarWidget::SetWatchedComponent(UDamageSystemComponent* NewComponent)
{
	if (WatchedComponent.IsValid())
	{
		WatchedComponent -> OnHealthChanged.RemoveDynamic(this, &UHealthBarWidget::HandleHealthChanged);
	}
	
	WatchedComponent = NewComponent;
	if (NewComponent)
	{
		NewComponent -> OnHealthChanged.AddDynamic(this, &UHealthBarWidget::HandleHealthChanged);
		UpdateDisplay(NewComponent -> GetCurrentHealth(), NewComponent -> GetMaxHealth());
	}
}

void UHealthBarWidget::NativeDestruct()
{
	SetWatchedComponent(nullptr);
	Super::NativeDestruct();
}

void UHealthBarWidget::HandleHealthChanged(float NewCurrentHealth, float NewMaxHealth)
{
	UpdateDisplay(NewCurrentHealth, NewMaxHealth);
}

void UHealthBarWidget::UpdateDisplay(float Current, float Max)
{
	const float Percent = (Max > 0.0f) ? Current / Max : 0.0f;
	if (HealthBar) { HealthBar -> SetPercent(Percent); }
	
	if (HealthText)
	{
		HealthText -> SetText(FText::FromString
			(FString::Printf(TEXT("%d / %d"), FMath::CeilToInt(Current), FMath::CeilToInt(Max))));
	}
	
	OnHealthUpdated(Current, Max);
}