// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Global/URStructs.h"
#include "UR_ItemSlot.generated.h"

// �κ��丮 ���Կ��� �������� ���������� �����ϱ����� Ŭ�����̴�
UCLASS()
class UNREALPROJ_API UUR_ItemSlot : public UUserWidget
{
	GENERATED_BODY()

private:
	const FURItemData* m_Data;

	class UImage* m_Image;

	class UTextBlock* m_ItemCountText;

	FString m_BlockText;


public:
	// URealUn_ItemSlot();

	FORCEINLINE const FURItemData* GetItemData()
	{ 
		return m_Data;
	}

	FORCEINLINE void SetItemData(const FURItemData* _Data)
	{ 
		m_Data = _Data;
	}

protected:
	// ���������ǰ�� �����ڴ�� �̰��� �̿��Ѵ�.
	void NativeConstruct() override;

private:
	UFUNCTION(BlueprintCallable, Category = "Contents", meta = (AllowPrivateAccess = "true"))
	void SlotInit();
};
