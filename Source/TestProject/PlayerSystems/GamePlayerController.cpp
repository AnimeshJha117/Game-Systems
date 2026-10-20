#include "GamePlayerController.h"
#include "../UI/HealthBarWidget.h"
#include "../DamageSystem/DamageSystemComponent.h"
#include "../UI/ScreenFlashWidget.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Engine/LocalPlayer.h"

void AGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsLocalController()) { return; }
	
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			LocalPlayer -> GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			for (UInputMappingContext* Context : DefaultMappingContexts)
			{
				if (Context) Subsystem -> AddMappingContext(Context, 0);
			}
		}
	}
}

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

void AGamePlayerController::FlashScreen(FLinearColor Color, float Intensity)
{
	if (!IsLocalController() || !FlashWidgetClass) { return; }
	
	if (!FlashWidget)
	{
		FlashWidget = CreateWidget<UScreenFlashWidget>(this, FlashWidgetClass);
		FlashWidget -> AddToViewport(-1);
	}
	
	FlashWidget -> PlayFlash(Color, Intensity);
}