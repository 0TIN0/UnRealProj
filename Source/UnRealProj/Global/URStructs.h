// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "URStructs.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UURStructs : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(Atomic, BlueprintType)
struct FURMonsterDataInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// double는 경단위로 표현가능하기때문에 요즘은 int를 사용 안 하고 double자료형을 사용한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double HP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Def;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double MinAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double MaxAttack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Speed;
};
