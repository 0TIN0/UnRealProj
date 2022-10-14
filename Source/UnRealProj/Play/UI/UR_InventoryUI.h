// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UR_InventoryUI.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_InventoryUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void InventroyInit(class UTileView* _TileView, int32 _Count);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	int AddInvenItemEvent(UObject* _StartData, UUserWidget* _Slot);

	bool IsFull(const struct FURItemData* _ItemData);

	void AddItem(const struct FURItemData* _ItemData);

private:
	TArray<class UUR_ItemSlot*> m_ItemSlot;

	int m_InitItemCount;
};
