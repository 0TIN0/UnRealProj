// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DecalActor.h"
#include "Global/UREnum.h"
#include "UR_RainPosDecal.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AUR_RainPosDecal : public ADecalActor
{
	GENERATED_BODY()

public:
	AUR_RainPosDecal();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor> m_HoldActor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor> m_BurstActor;

	float m_DestroyTime;

	SparrowAttack_Type m_AttackType;

	const struct FURMonsterDataInfo* m_Data;

public:
	void SetData(const struct FURMonsterDataInfo* _Data)
	{
		m_Data = _Data;
	}

	void SetAttackType(SparrowAttack_Type _Type)
	{
		m_AttackType = _Type;
	}

	void SetAttackType(int _Type)
	{
		m_AttackType = static_cast<SparrowAttack_Type>(_Type);
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
