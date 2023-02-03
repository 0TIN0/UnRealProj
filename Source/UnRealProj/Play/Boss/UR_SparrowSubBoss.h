// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/URAICharacter.h"
#include "UR_SparrowSubBoss.generated.h"

UENUM(BlueprintType)
enum class SparrowBossAnimation : uint8
{
	// 1100 
	Default UMETA(DisplayName = "Don't touch"),
	RainShootStart = static_cast<int>(DefaultAnimation::Max) UMETA(DisPlayName = "RainShootStart"),
	RainShootAndEnd UMETA(DisPlayName = "RainShootAndEnd"),
	RainShootHold UMETA(DisPlayName = "RainShootHold"),
	RainShootBurst UMETA(DisPlayName = "RainShootBurst"),
	SPShootStart UMETA(DisPlayName = "SPShootStart"),	// 기본 Shoot 동작
	SPShootHold UMETA(DisPlayName = "SPShootHold"),
	SPShootEnd UMETA(DisPlayName = "SPShootEnd"),
	SP1 UMETA(DisPlayName = "SP1"),
	SP2End UMETA(DisPlayName = "SP2End"),
	SP3End UMETA(DisPlayName = "SP3End"),
	SP4End UMETA(DisPlayName = "SP4End"),
	SP5End UMETA(DisPlayName = "SP5End"),
	ShootCancel UMETA(DisPlayName = "ShootCancel"),
	BurstShoot UMETA(DisPlayName = "BurstShoot"),
	Spawn UMETA(DisPlayName = "Spawn"),
	Max UMETA(DisPlayName = "Max")
};
UCLASS()
class UNREALPROJ_API AUR_SparrowSubBoss : public AURAICharacter
{
	GENERATED_BODY()

public:
	AUR_SparrowSubBoss();

	bool FindBossAnimMontage(const SparrowBossAnimation _Key)
	{
		if (GetAnimationInstance()->GetAnimation(_Key))
		{
			return true;
		}

		return false;
	};

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> m_BowMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> m_ArrowMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		TObjectPtr<class USpringArmComponent> m_IconArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> m_PlaneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossAnimationData", meta = (AllowPrivateAccess = "true"))
		TMap<SparrowBossAnimation, UAnimMontage*> m_BossAnimations;

	const struct FURMonsterDataInfo* m_SparrowData;

	SparrowAttack_Type m_RandAttackNumb;

public:
	const struct FURMonsterDataInfo* BossDataInit();

	const struct FURMonsterDataInfo* GetSparrowData()
	{
		return m_SparrowData;
	}

	void SetRandAttackNumb(int RandNumb)
	{
		m_RandAttackNumb = static_cast<SparrowAttack_Type>(RandNumb);
	}

	SparrowAttack_Type GetRandAttackNumb()	const
	{
		return m_RandAttackNumb;
	}

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;
	void DamageOn(bool _IsKnockBack = true) override;
	void DamageOff() override;
	void CallDamage(double _Damage, AActor* _Actor = nullptr, bool _IsKnockBack = true, bool _IsCameraShake = true) override;
	
};
