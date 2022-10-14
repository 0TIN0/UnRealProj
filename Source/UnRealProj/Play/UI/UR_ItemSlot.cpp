// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/UI/UR_ItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUR_ItemSlot::SlotInit()
{
	m_Image = Cast<UImage>(GetWidgetFromName(FName(TEXT("ItemIconImage"))));

	if (nullptr == m_Image)
	{
		UE_LOG(LogTemp, Error, TEXT("Item Image nullptr!"));
		return;
	}

	m_ItemCountText = Cast<UTextBlock>(GetWidgetFromName(TEXT("ItemIconCount")));

	if (nullptr == m_ItemCountText)
	{
		UE_LOG(LogTemp, Error, TEXT("Item Text Nullptr!"));
		return;
	}


	m_ItemCountString = TEXT("");

	m_Data = nullptr;
}

void UUR_ItemSlot::SetItemData(const FURItemData* _Data)
{
	// 장비템인지 소비템인지 나눔
	if (_Data->ItemType == ContentsItemType::Equip)
	{
		m_ItemCountString = TEXT("");
	}
	else if (_Data->ItemType == ContentsItemType::Consumable)
	{
		if (m_ItemCountString == TEXT(""))
		{
			// 처음들어가는것이라면 0을 넣어준다.
			m_ItemCountString = FString::FromInt(1);
		}
		else
		{
			// 그게 아니라면 기존의 숫자에서 +1을 해주어야한다.
			int Count = FCString::Atoi(*m_ItemCountString);

			++Count;

			m_ItemCountString = FString::FromInt(Count);
		}
	}

	// 데이터 테이블에 저장해놓은 아이콘 텍스처로 지정해준다.
	m_Image->SetBrushFromTexture(_Data->IconTexture);

	// 데이터 갱신
	m_Data = _Data;
}

void UUR_ItemSlot::NativeConstruct()
{
	int a = 0;
}
