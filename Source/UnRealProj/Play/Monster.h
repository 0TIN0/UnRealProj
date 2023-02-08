// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "URAICharacter.h"
#include "Monster.generated.h"

USTRUCT()
struct FURAI_STRUCT
{
	GENERATED_USTRUCT_BODY()

		bool IsAttack;
	bool IsBackMove;

	FURAI_STRUCT()	:
		IsAttack(false),
		IsBackMove(false)
	{

	}
};
UCLASS()
class UNREALPROJ_API AMonster : public AURAICharacter
{
	GENERATED_BODY()

public:
	AMonster();

	FORCEINLINE const struct FURMonsterDataInfo* GetMonsterData()
	{
		return m_MonsterData;
	}

	const struct FURMonsterDataInfo* MonsterDataInit();

protected:
	void DamageOn(bool _IsKnockBack = true) override;
	void DamageOff() override;
	void CallDamage(double _Damage, AActor* _Actor = nullptr, bool _IsKnockBack = true, bool _IsCameraShake = true) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	TObjectPtr<class USphereComponent> m_DamageCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	TObjectPtr<class USpringArmComponent> m_IconArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> m_PlaneComponent;

	// 추가적인 애니메이션
	UPROPERTY(Category = "PlayerAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TMap<PirateAnimation, UAnimMontage*> m_PirateAnimations;

	const struct FURMonsterDataInfo* m_MonsterData;

	TArray<const struct FURItemData*> m_DropTable;

	bool m_IsDamageCheck;

	bool m_IsUltimateHit;

	float m_PushTime;

	FVector m_UltimateHitDir;

	class APlayCharacter* m_Player;

	int m_BlockCount;

	FURAI_STRUCT m_AIStruct;

public:
	void SetUltimateHitDir(const FVector& Dir)
	{
		m_UltimateHitDir = Dir;
	}

	void SetUltimateHitEnable(bool Enable)
	{
		m_IsUltimateHit = Enable;
	}

	bool GetUltimateHitEnable()	 const
	{
		return m_IsUltimateHit;
	}

	int GetBlockCount()	const
	{
		return m_BlockCount;
	}

	FURAI_STRUCT GetAIStruct()	const
	{
		return m_AIStruct;
	}

	void SetAIIsAttack(bool _Enable)
	{
		m_AIStruct.IsAttack = _Enable;
	}

	void SetAIIsBackMove(bool _Enable)
	{
		m_AIStruct.IsBackMove = _Enable;
	}


protected:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void NotifyActorEndOverlap(AActor* OtherActor) override;
	
};
