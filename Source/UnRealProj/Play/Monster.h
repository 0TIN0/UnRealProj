// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "URCharacter.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AMonster : public AURCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowprivateAccess = "true"))
	FName m_MonsterStatusKey;

	const struct FURMonsterDataInfo* m_MonsterData;

protected:
	void BeginPlay() override;
	
};
