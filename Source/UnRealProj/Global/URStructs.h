// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "../Play/URCharacter.h"
#include "Components/StaticMeshComponent.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double AttRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<DefaultAnimation, class UAnimMontage*> Animations;
};

USTRUCT(Atomic, BlueprintType)
struct FURPlayerDataInfo : public FTableRowBase
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
	TMap<DefaultAnimation, class UAnimMontage*> Animations;
};

USTRUCT(Atomic, BlueprintType)
struct FURObjectTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		// double�� ������� ǥ�������ϱ⶧���� ������ int�� ��� �� �ϰ� double�ڷ����� ����Ѵ�.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UObject> ObjectSubClass;
};

USTRUCT(Atomic, BlueprintType)
struct FURItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;
	// �������� ������Ÿ�� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ContentsItemType	ItemType;

	// �κ��丮 �����ܿ� ���� �ؽ�ó
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* IconTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* DropMesh;

	// ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HP;

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MP;
};