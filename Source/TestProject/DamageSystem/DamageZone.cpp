#include "DamageZone.h"
#include "DamagableInterface.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

ADamageZone::ADamageZone()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ZoneBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Zone_Box"));
	SetRootComponent(ZoneBox);
	ZoneBox -> SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	ZoneBox -> SetBoxExtent(FVector(200.0f, 200.0f, 50.0f));
}

void ADamageZone::BeginPlay()
{
	Super::BeginPlay();
	ZoneBox -> OnComponentBeginOverlap.AddDynamic(this, &ADamageZone::OnZoneBeginOverlap);
}

void ADamageZone::OnZoneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!GetWorldTimerManager().IsTimerActive(DamageTimerHandle))
	{
		GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ADamageZone::ApplyDamageToOverlapping, TickInterval, true, 0.0f);
	}
}

void ADamageZone::ApplyDamageToOverlapping()
{
	TArray<AActor*> Overlapping;
	ZoneBox -> GetOverlappingActors(Overlapping);
	
	if (Overlapping.IsEmpty())
	{
		GetWorldTimerManager().ClearTimer(DamageTimerHandle);
		return;
	}
	
	FDamageInfo DamageInfo;
	DamageInfo.DamageAmount = DamagePerTick;
	DamageInfo.DamageDealer = this;
	DamageInfo.DamageType = DamageType;
	DamageInfo.DamageResponse = DamageResponse;
	
	for (AActor* Actor : Overlapping)
	{
		if (Actor && Actor -> Implements<UDamagableInterface>())
		{
			IDamagableInterface::Execute_TakeDamage(Actor, DamageInfo);
		}
	}
}