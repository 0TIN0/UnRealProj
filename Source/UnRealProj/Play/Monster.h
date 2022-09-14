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


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	FName m_MonsterStatusKey;

	const struct FURMonsterDataInfo* m_MonsterData;

protected:
	void BeginPlay() override;
	
};