// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UREnum.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUREnum : public UObject
{
	GENERATED_BODY()

};

UENUM(BlueprintType)
enum class DefaultAnimation : uint8
{
	// 1100 
	Default UMETA(DisplayName = "애니메이션 지정안됨"),
	Idle UMETA(DisplayName = "서있는 모션"),
	Left UMETA(DisplayName = "왼쪽"),
	Right  UMETA(DisplayName = "오른쪽"),
	Forward UMETA(DisplayName = "앞"),
	BackWard UMETA(DisplayName = "뒤"),
	Attack UMETA(DisplayName = "공격모션"),
	Hit UMETA(DisplayName = "히트모션"),
	Max UMETA(DisplayName = "최대치"),
};

UENUM(BlueprintType)
enum class ContentsItemType : uint8
{
	// 사용x
	Default UMETA(DisplayName = "사용x"),
	// 겹칠 수 없는 아이템
	Equip UMETA(DisplayName = "장비"),
	// 겹칠 수 있는 아이템
	Consumable UMETA(DisPlayName = "소비")
};