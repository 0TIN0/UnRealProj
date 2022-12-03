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
	Spawn UMETA(DisPlayName = "Spawn")
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

	TSubclassOf<class AActor> GetSpawnActorClass()	const
	{
		return m_SpawnActorClass;
	}
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> m_IconArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> m_PlaneComponent;

	UPROPERTY(Category = "BossAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<BossAnimation, UAnimMontage*> m_BossAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor>	m_SpawnActorClass;

	const struct FURMonsterDataInfo* m_BossData;

	int m_RandNumb;

public:
	const struct FURMonsterDataInfo* BossDataInit();

	FORCEINLINE const struct FURMonsterDataInfo* GetMonsterData()
	{
		return m_BossData;
	}

	FORCEINLINE int GetRandNumb()	const
	{
		return m_RandNumb;
	}

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;
	void DamageOn() override;
	void DamageOff() override;
	void CallDamage(double _Damage, AActor* _Actor = nullptr) override;
	
};