#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageSystemTypes.h"
#include "DamageZone.generated.h"

class UBoxComponent;

UCLASS()
class TESTPROJECT_API ADamageZone : public AActor
{
	GENERATED_BODY()

public:
	ADamageZone();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnZoneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	void ApplyDamageToOverlapping();
	
	UPROPERTY(VisibleAnywhere, Category = "Damage Zone")
	TObjectPtr<UBoxComponent> ZoneBox;
	
	UPROPERTY(EditAnywhere, Category = "Damage Zone")
	float DamagePerTick {10.0f};
	
	UPROPERTY(EditAnywhere, Category = "Damage Zone")
	float TickInterval {1.0f};
	
	UPROPERTY(EditAnywhere, Category = "Damage Zone")
	EDamageType DamageType {EDamageType::Environmental};
	
	UPROPERTY(EditAnywhere, Category = "Damage Zone")
	EDamageResponse DamageResponse {EDamageResponse::HitReaction};
	
private:
	FTimerHandle DamageTimerHandle;
};