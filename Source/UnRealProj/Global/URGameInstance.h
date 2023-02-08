// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UREnum.h"
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

	struct FURPlayerDataInfo* GetPlayerData(FName Name) const;

	const struct FURItemData* GetItemData(FName Name)	const;

	const TSubclassOf<AActor> GetGetObjectData(FName Name)	const;

	// 랜덤한 아이템을 드롭하기위한 함수
	TArray<const struct FURItemData*> GetRandomDropData(int _Count);

	FORCEINLINE FRandomStream& GetRandomStream() { return m_Stream; }

	FORCEINLINE class UUR_InventoryUI* GetInven()
	{
		return m_Inven;
	}

	FORCEINLINE void SetInven(class UUR_InventoryUI* _Inven)
	{
		m_Inven = _Inven;
	}

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

	class UUR_InventoryUI* m_Inven;

	bool m_DebugCheck;

	// 플레이어 퀘스트 저장관련
	QuestProgress m_SaveQuest;
	bool m_IsSaveQuestCompletion;
	bool m_IsSaveQuesting;

	bool m_IsSaveEnable;


public:
	UFUNCTION(BlueprintCallable, Category = UR)
	void QuestSavePush(QuestProgress _Quest, bool _IsSAveQuestCompletion, bool _IsSaveQuesting);

	void QuestSaveFull(class AURCharacter* _Character);
};
