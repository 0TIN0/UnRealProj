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

	const struct FURItemData* GetItemData(FName Name)	const;

	const TSubclassOf<UObject> GetGetObjectData(FName Name)	const;

	// 랜덤한 아이템을 드롭하기위한 함수
	TArray<const struct FURItemData*> GetRandomDropData(int _Count);

	FORCEINLINE FRandomStream& GetRandomStream() { return m_Stream; }

	void DebugSwitch();

	FORCEINLINE bool IsDebug()	const
	{
		return m_DebugCheck;
	}

private:
	TSoftObjectPtr<class UDataTable> m_MonsterDataTable;

	TSoftObjectPtr<class UDataTable> m_PlayerDataTable;

	TSoftObjectPtr<class UDataTable> m_ObjectDataTable;

	TSoftObjectPtr<class UDataTable> m_ItemDataTable;

	TArray<int32> m_ItemRandomTableIndex;

	TArray<FURItemData*> m_ItemDataRandomTable;

	FRandomStream m_Stream;

	bool m_DebugCheck;
};
