#include "GamePlayerController.h"
#include "HealthBarWidget.h"
#include "DamageSystemComponent.h"

void AGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!IsLocalController() || !HealthBarWidgetClass) { return; }

	if (!HealthWidget)
	{
		HealthWidget = CreateWidget<UHealthBarWidget>(this, HealthBarWidgetClass);
		HealthWidget -> AddToViewport();
	}
	
	HealthWidget->SetWatchedComponent(InPawn->FindComponentByClass<UDamageSystemComponent>());
}

void AGamePlayerController::OnUnPossess()
{
	if (HealthWidget) { HealthWidget->SetWatchedComponent(nullptr); }
	Super::OnUnPossess();
}