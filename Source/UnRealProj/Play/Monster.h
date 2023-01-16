// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "URAICharacter.h"
#include "Monster.generated.h"



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

	const struct FURMonsterDataInfo* m_MonsterData;

	TArray<const struct FURItemData*> m_DropTable;

	bool m_IsDamageCheck;

	bool m_IsUltimateHit;

	float m_PushTime;

	FVector m_UltimateHitDir;

	class APlayCharacter* m_Player;

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

protected:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void NotifyActorEndOverlap(AActor* OtherActor) override;
	
};
