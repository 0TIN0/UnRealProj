// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/UI/UR_ItemSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UUR_ItemSlot::NativeConstruct()
{
	int a = 0;
}

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

}
