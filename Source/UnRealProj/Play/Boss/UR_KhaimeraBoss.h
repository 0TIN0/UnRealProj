// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/URAICharacter.h"
#include "UR_KhaimeraBoss.generated.h"

UENUM(BlueprintType)
enum class KhaimeraBossAnimation : uint8
{
	// 1100 
	Default UMETA(DisplayName = "Don't touch"),
	FowardAttack1 = static_cast<int>(DefaultAnimation::Max) UMETA(DisplayName = "FowardAttack1"),
	FowardAttack2 UMETA(DisplayName = "FowardAttack2"),
	FowardAttack3 UMETA(DisplayName = "FowardAttack3"),
	FowardCombo1 UMETA(DisplayName = "Combo1"),
	FowardFastComboAttack UMETA(DisplayName = "FowardFastComboAttack"),
	Attack1Recovery UMETA(DisplayName = "Attack1Recovery"),
	Attack2Recovery UMETA(DisplayName = "Attack2Recovery"),
	Attack3Recovery UMETA(DisplayName = "Attack3Recovery"),
	BerserkStart UMETA(DisplayName = "BerserkStart"),
	DashStart UMETA(DisplayName = "DashStart"),
	DashAttack UMETA(DisplayName = "DashAttack"),
	UltimateAttackStart UMETA(DisplayName = "UltimateAttackStart"),
	UltimateAttack UMETA(DisplayName = "UltimateAttack"),
	Spawn UMETA(DisPlayName = "Spawn"),
	StunStart UMETA(DisPlayName = "StunStart"),
	StunLoop UMETA(DisPlayName = "StunLoop"),
	StunEnd UMETA(DisPlayName = "StunEnd"),
	RushAttackStart UMETA(DisPlayName = "RushAttackStart"),
	RushAttack UMETA(DisPlayName = "RushAttack"),
	Max UMETA(DisPlayName = "Max")
};

UCLASS()
class UNREALPROJ_API AUR_KhaimeraBoss : public AURAICharacter
{
	GENERATED_BODY()

public:
	AUR_KhaimeraBoss();

	bool FindBossAnimMontage(const KhaimeraBossAnimation _Key)
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
		TObjectPtr<class USphereComponent> m_LDamageCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		TObjectPtr<class USphereComponent> m_RDamageCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		TObjectPtr<class USpringArmComponent> m_IconArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> m_PlaneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BossAnimationData", meta = (AllowPrivateAccess = "true"))
		TMap<KhaimeraBossAnimation, UAnimMontage*> m_BossAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>	m_SpawnActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
		class USkeletalMesh* m_BerserkerMesh;


	class AUR_BlackHole* m_BlackHole;

	float m_SpawnRange;

	const struct FURMonsterDataInfo* m_KhaimeraData;

	int m_RandNumb;

	bool m_IsBerserk;

	float m_BlackHoleSpawnTime;

public:
	const struct FURMonsterDataInfo* BossDataInit();

	const struct FURMonsterDataInfo* GetKhaimeraData()
	{
		return m_KhaimeraData;
	}

	FORCEINLINE int GetRandNumb()	const
	{
		return m_RandNumb;
	}

	bool GetIsBerserk()	const
	{
		return m_IsBerserk;
	}

	void SetIsBerserk(bool _Enable)
	{
		m_IsBerserk = _Enable;
	}

	void SetBerserkMesh();

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;
	void DamageOn(bool _IsKnockBack = true) override;
	void DamageOff() override;
	void CallDamage(double _Damage, AActor* _Actor = nullptr, bool _IsKnockBack = true, bool _IsCameraShake = true) override;


private:
	void CreateBlackHole();
	
};
