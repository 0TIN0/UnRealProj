// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "URGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UURGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UURGameInstance();

	const struct FURMonsterDataInfo* GetMonsterData(FName Name) const;

private:
	TSoftObjectPtr<class UDataTable> MonsterDataTable;
};
