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


// 데이터를 직렬화 해서 메모리를 아끼라는 건데
// 데이터를 수천수만개 써야할때 속력을 빠르게 해줍니다.
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<DefaultAnimation, class UAnimMontage*> Animations;
};

USTRUCT(Atomic, BlueprintType)
struct FURObjectTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

		// double는 경단위로 표현가능하기때문에 요즘은 int를 사용 안 하고 double자료형을 사용한다.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UObject> ObjectSubClass;
};

USTRUCT(Atomic, BlueprintType)
struct FURItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName DisplayName;
	// 아이템의 아이템타입 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ContentsItemType	ItemType;

	// 인벤토리 아이콘에 사용될 텍스처
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* IconTexture;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMesh* DropMesh;

	// 체력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int HP;

	// 마력
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MP;
};