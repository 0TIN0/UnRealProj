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
	}
}

void UUR_InventoryUI::AddInvenItemEvent(UObject* _StartData, UUserWidget* _Slot)
{
	UUR_InvenSlotData* Data = Cast<UUR_InvenSlotData>(_StartData);

	if (nullptr == Data)
	{
		return;
	}


	UUR_ItemSlot* Widget = Cast<UUR_ItemSlot>(_Slot);

	if (nullptr == Widget)
	{
		return;
	}

	m_ItemSlot.Add(Widget);
}
