// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "URAICharacter.h"
#include "Monster.generated.h"

/**
 * 
 */
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

	void DamageOn() override;
	void DamageOff() override;
	void CallDamage(double _Damage) override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	class USphereComponent* m_DamageCollision;

	const struct FURMonsterDataInfo* m_MonsterData;

	bool m_IsDamageCheck;

protected:
	void BeginPlay() override;

	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void NotifyActorEndOverlap(AActor* OtherActor) override;
	
};
