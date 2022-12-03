// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Global/URStructs.h"
#include "UR_ItemSlot.generated.h"

// 인벤토리 슬롯에서 아이콘을 개별적으로 관리하기위한 클래스이다
UCLASS()
class UNREALPROJ_API UUR_ItemSlot : public UUserWidget
{
	GENERATED_BODY()

protected:
	// 유저위젯의경우 생성자대신 이것을 이용한다.
	void NativeConstruct() override;

private:
	const FURItemData* m_Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UImage* m_Image;

	class UTextBlock* m_ItemCountText;

	FString m_BlockText;
	
	// 에디터에서 바인딩을 통해 c++이건 에디터건 값을 지정해줄 수 있음.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FString m_ItemCountString;


public:
	// URealUn_ItemSlot();

	FORCEINLINE const FURItemData* GetItemData()
	{ 
		return m_Data;
	}

	void SetItemData(const FURItemData* _Data);

	UFUNCTION(BlueprintCallable, Category = "Contents", meta = (AllowPrivateAccess = "true"))
	class UImage* GetItemSlotImage()	const
	{
		return m_Image;
	}

	UFUNCTION(BlueprintCallable, Category = "Contents", meta = (AllowPrivateAccess = "true"))
	FName GetIconDisPlayName()	const
	{
		return m_Data->DisplayName;
	}

	UFUNCTION(BlueprintCallable, Category = "Contents", meta = (AllowPrivateAccess = "true"))
	void SetItemIconImage(UImage* _Image)
	{
		m_Image = _Image;
	}


private:
	UFUNCTION(BlueprintCallable, Category = "Contents", meta = (AllowPrivateAccess = "true"))
	void SlotInit();
};
