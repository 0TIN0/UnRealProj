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


// �����͸� ����ȭ �ؼ� �޸𸮸� �Ƴ���� �ǵ�
// �����͸� ��õ������ ����Ҷ� �ӷ��� ������ ���ݴϴ�.
USTRUCT(Atomic, BlueprintType)
struct FURMonsterDataInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// double�� ������� ǥ�������ϱ⶧���� ������ int�� ��� �� �ϰ� double�ڷ����� ����Ѵ�.
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double FindRange;
};
