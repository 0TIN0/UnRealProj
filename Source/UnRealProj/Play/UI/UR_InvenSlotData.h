// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Global/UREnum.h"
#include "Global/URStructs.h"
#include "UR_InvenSlotData.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_InvenSlotData : public UObject
{
	GENERATED_BODY()

public:
	const FURItemData* ItemData;
	
};
