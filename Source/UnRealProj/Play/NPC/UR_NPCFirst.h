// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/URCharacter.h"
#include "UR_NPCFirst.generated.h"

UENUM(BlueprintType)
enum class NPCAnimation : uint8
{
	// 1100 
	Min UMETA(DisplayName = "Don't touch"),
	EMotion1 = static_cast<int>(DefaultAnimation::Max) UMETA(DisplayName = "EMotion1"),
	EMotion2 UMETA(DisplayName = "EMotion2"),
	EMotion3 UMETA(DisPlayName = "EMotion3")
};

UCLASS()
class UNREALPROJ_API AUR_NPCFirst : public AURCharacter
{
	GENERATED_BODY()

public:
	AUR_NPCFirst();

private:
	UPROPERTY(Category = "NPCAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<NPCAnimation, UAnimMontage*> m_NPCAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* m_InteractionBox;

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;
	
};
