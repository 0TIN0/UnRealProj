// Fill out your copyright notice in the Description page of Project Settings.


#include "URGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Global/URStructs.h"

UURGameInstance::UURGameInstance()
{
    {
        FString DataPath = TEXT("DataTable'/Game/Resource/Global/NewDataTable.NewDataTable'");

        // 리소스를 로드하는 용도
        ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

        // 찾는것을 성공했다면 데이터테이블을 얻어온 녀석으로 바꿔준다.
        if (DataTable.Succeeded())
        {
            MonsterDataTable = DataTable.Object;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MonsterDatas Null!"));
        }
    }
}

const FURMonsterDataInfo* UURGameInstance::GetMonsterData(FName Name) const
{
    FURMonsterDataInfo* DataInfo = MonsterDataTable->FindRow<FURMonsterDataInfo>(Name, Name.ToString());

    if (!DataInfo)
    {
        return nullptr;
    }

    return DataInfo;
}
