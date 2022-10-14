// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/URAICharacter.h"
#include "UR_BossMonster.generated.h"

UENUM(BlueprintType)
enum class BossAnimation : uint8
{
	// 1100 
	Min UMETA(DisplayName = "Don't touch"),
	Skill1 = static_cast<int>(DefaultAnimation::Max) UMETA(DisplayName = "Skill1"),
	Skill2 UMETA(DisplayName = "Skill2"),
	Skill3 UMETA(DisplayName = "Skill3"),
};

UCLASS()
class UNREALPROJ_API AUR_BossMonster : public AURAICharacter
{
	GENERATED_BODY()

public:
	AUR_BossMonster();

	bool FindBossAnimMontage(const BossAnimation _Key)
	{
		if (GetAnimationInstance()->GetAnimation(_Key))
		{
			return true;
		}

		return false;
	};
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> m_IconArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> m_PlaneComponent;

	UPROPERTY(Category = "BossAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<BossAnimation, UAnimMontage*> m_BossAnimations;

	const struct FURMonsterDataInfo* m_BossData;

public:
	const struct FURMonsterDataInfo* BossDataInit();

	FORCEINLINE const struct FURMonsterDataInfo* GetMonsterData()
	{
		return m_BossData;
	}

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;
	void DamageOn() override;
	void DamageOff() override;
	void CallDamage(double _Damage) override;
	
};