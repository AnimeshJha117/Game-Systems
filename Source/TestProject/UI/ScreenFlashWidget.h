#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenFlashWidget.generated.h"

UCLASS(Abstract)
class TESTPROJECT_API UScreenFlashWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Screen Flash")
	void PlayFlash(FLinearColor Color, float Intensity);
};