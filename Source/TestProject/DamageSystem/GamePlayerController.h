#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

class UHealthBarWidget;
class UScreenFlashWidget;

UCLASS()
class TESTPROJECT_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void FlashScreen(FLinearColor Color, float Intensity = 1.0f);
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TArray<TObjectPtr<class UInputMappingContext>> DefaultMappingContexts;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UHealthBarWidget> HealthBarWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UHealthBarWidget> HealthWidget;
	
	UPROPERTY (EditDefaultsOnly, Category = "UI")
	TSubclassOf<UScreenFlashWidget> FlashWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UScreenFlashWidget> FlashWidget;
};