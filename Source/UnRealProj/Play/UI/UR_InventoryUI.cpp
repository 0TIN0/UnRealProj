// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/UI/UR_InventoryUI.h"
#include "Global/URGameInstance.h"
#include "Global/ConstantValues.h"
#include "UR_InvenSlotData.h"
#include "Components/TileView.h"
#include "UR_ItemSlot.h"

void UUR_InventoryUI::InventroyInit(UTileView* _TileView, int32 _Count)
{
	if (!_TileView)
	{
		return;
	}

	UURGameInstance* Inst = GetWorld()->GetGameInstance<UURGameInstance>();

	if (!Inst && 
		!Inst->IsValidLowLevel())
	{
		return;
	}

	const FURItemData* ItemData = Inst->GetItemData(ItemNames::NoneItem);

	for (size_t i = 0; i < _Count; ++i)
	{
		UUR_InvenSlotData* InvenSlot = NewObject<UUR_InvenSlotData>();
		InvenSlot->ItemData = ItemData;
		_TileView->AddItem(InvenSlot);

		//m_ItemSlot.Add(Cast<UUR_ItemSlot>(_TileView->GetDisplayedEntryWidgets()));
	}

	m_InitItemCount = _Count;
	// 게임 인스턴스에 인벤토리를 들고있도록 설정
	// 다른곳에서도 인벤토리를 얻어서 조작할 수 있음.
	Inst->SetInven(this);
}

int UUR_InventoryUI::AddInvenItemEvent(UObject* _StartData, UUserWidget* _Slot)
{
	UUR_InvenSlotData* Data = Cast<UUR_InvenSlotData>(_StartData);

	if (nullptr == Data)
	{
		return 1;
	}

	UUR_ItemSlot* Widget = Cast<UUR_ItemSlot>(_Slot);

	if (nullptr == Widget)
	{
		return 1;
	}

	m_ItemSlot.Add(Widget);

	return --m_InitItemCount;
}

bool UUR_InventoryUI::IsFull(const FURItemData* _ItemData)
{
	if (!_ItemData)
	{
		return false;
	}

	// 장비랑 소비템이랑 처리방식이 다르다.
	if (_ItemData->ItemType == ContentsItemType::Equip)
	{
		for (size_t i = 0; i < m_ItemSlot.Num(); ++i)
		{
			// 단 한개라도 인벤슬롯이 널이라면 꽉차있지 않다는 의미이다.
			if (!m_ItemSlot[i]->GetItemData())
			{
				return false;
			}
		}
	}
	else if (_ItemData->ItemType == ContentsItemType::Consumable)
	{
		for (size_t i = 0; i < m_ItemSlot.Num(); ++i)
		{
			// 소비아이템의 경우 겹쳐지기 때문에 같은 타입의 데이터가 있다면 꽉 차지 않았다는 의미
			if (_ItemData == m_ItemSlot[i]->GetItemData())
			{
				return false;
			}

			// 단 한개라도 인벤슬롯이 널이라면 꽉차있지 않다는 의미이다.
			if (!m_ItemSlot[i]->GetItemData())
			{
				return false;
			}
		}
	}

	// 그게 전부 아니라면 꽉 차있다는 의미이다.
	return true;
}

void UUR_InventoryUI::AddItem(const FURItemData* _ItemData)
{
	if (!_ItemData)
	{
		return;
	}

	if (_ItemData->ItemType == ContentsItemType::Equip)
	{
		for (size_t i = 0; i < m_ItemSlot.Num(); ++i)
		{
			// 널이 아니라면 해당 인덱스 슬롯에 아이템이 있다는 의미이므로 다음 인덱스로 넘어간다.
			if (m_ItemSlot[i]->GetItemData())
			{
				continue;
			}
			// 그게 아니라면 없다는 의미이므로 해당 인덱스 슬롯에 아이템을 넣어주고 더이상 처리할 필요가 없으므로 리턴
			m_ItemSlot[i]->SetItemData(_ItemData);
			return;
		}
	}
	else if (_ItemData->ItemType == ContentsItemType::Consumable)
	{
		for (size_t i = 0; i < m_ItemSlot.Num(); ++i)
		{
			if (_ItemData == m_ItemSlot[i]->GetItemData())
			{
				m_ItemSlot[i]->SetItemData(_ItemData);
				return;
			}

			else if (m_ItemSlot[i]->GetItemData())
			{
				continue;
			}

			m_ItemSlot[i]->SetItemData(_ItemData);
			return;
		}
	}
}
