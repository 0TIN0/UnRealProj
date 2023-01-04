// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/URAICharacter.h"
#include "UR_KrakenBoss.generated.h"

UENUM(BlueprintType)
enum class KrakenBossAnimation : uint8
{
	// 1100 
	Min UMETA(DisplayName = "Don't touch"),
	FowardAttack1 = static_cast<int>(DefaultAnimation::Max) UMETA(DisplayName = "FowardAttack1"),
	FowardAttack2 UMETA(DisplayName = "FowardAttack2"),
	FowardComboAttack UMETA(DisplayName = "FowardComboAttack"),
	Spawn UMETA(DisPlayName = "Spawn")
};

UCLASS()
class UNREALPROJ_API AUR_KrakenBoss : public AURAICharacter
{
	GENERATED_BODY()

public:
	AUR_KrakenBoss();

	bool FindBossAnimMontage(const KrakenBossAnimation _Key)
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
		TObjectPtr<class USphereComponent> m_DamageCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		TObjectPtr<class USpringArmComponent> m_IconArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
		TObjectPtr<class UStaticMeshComponent> m_PlaneComponent;

	UPROPERTY(Category = "BossAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<KrakenBossAnimation, UAnimMontage*> m_BossAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skill", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>	m_SpawnActorClass;

	const struct FURMonsterDataInfo* m_KrakenData;

	int m_RandNumb;

public:
	const struct FURMonsterDataInfo* BossDataInit();

	const struct FURMonsterDataInfo* GetKrakenData()
	{
		return m_KrakenData;
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
	void CallDamage(double _Damage, AActor* _Actor = nullptr, bool _IsKnockBack = true) override;
	
};
