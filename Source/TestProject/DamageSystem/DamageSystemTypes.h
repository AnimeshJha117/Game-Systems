#pragma once

#include "CoreMinimal.h"
#include "DamageSystemTypes.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	None UMETA(DisplayName = "None"),
	Physical UMETA(DisplayName = "Physical"),
	Magical UMETA(DisplayName = "Magical"),
	Environmental UMETA(DisplayName = "Environmental"),
};

UENUM(BlueprintType)
enum class EDamageResponse : uint8
{
	None UMETA(DisplayName = "None"),
	HitReaction UMETA(DisplayName = "HitReaction"),
	Knockback UMETA(DisplayName = "Knockback"),
	Stun UMETA(DisplayName = "Stun"),
	Stagger UMETA(DisplayName = "Stagger"),
};

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageAmount {0.0f};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TObjectPtr<AActor> DamageDealer {nullptr};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EDamageType DamageType {EDamageType::None};
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	EDamageResponse DamageResponse {EDamageResponse::None};
};