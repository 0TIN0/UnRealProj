// Fill out your copyright notice in the Description page of Project Settings.


#include "URGameInstance.h"
#include "UObject/ConstructorHelpers.h"
#include "Global/URStructs.h"

UURGameInstance::UURGameInstance()
{
    m_Stream = FRandomStream(FDateTime::Now().GetTicks());
    {
        FString DataPath = TEXT("DataTable'/Game/Resource/Global/NewDataTable.NewDataTable'");

        // 리소스를 로드하는 용도
        ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

        // 찾는것을 성공했다면 데이터테이블을 얻어온 녀석으로 바꿔준다.
        if (DataTable.Succeeded())
        {
            m_MonsterDataTable = DataTable.Object;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MonsterDatas Null!"));
        }
    }

    {
        FString DataPath = TEXT("DataTable'/Game/Resource/Global/PlayerDataTable.PlayerDataTable'");

        // 리소스를 로드하는 용도
        ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

        // 찾는것을 성공했다면 데이터테이블을 얻어온 녀석으로 바꿔준다.
        if (DataTable.Succeeded())
        {
            m_PlayerDataTable = DataTable.Object;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MonsterDatas Null!"));
        }
    }

    {
        FString DataPath = TEXT("DataTable'/Game/Resource/Global/ItemDataTable.ItemDataTable'");

        // 리소스를 로드하는 용도
        ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

        // 찾는것을 성공했다면 데이터테이블을 얻어온 녀석으로 바꿔준다.
        if (DataTable.Succeeded())
        {
            m_ItemDataTable = DataTable.Object;

            // 데이타 테이블 정보를 얻어온다.
            m_ItemDataTable->GetAllRows(nullptr, m_ItemDataRandomTable);

            // 개수만큼 인덱스값을 넣어주는데 0번은 None값이기때문에 1번부터 넣어줌
            for (size_t i = 1; i < m_ItemDataRandomTable.Num(); ++i)
            {
                m_ItemRandomTableIndex.Add(i);
            }
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MonsterDatas Null!"));
        }
    }


    {
        FString DataPath = TEXT("DataTable'/Game/Resource/Global/ObjectDataTable.ObjectDataTable'");

        // 리소스를 로드하는 용도
        ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

        // 찾는것을 성공했다면 데이터테이블을 얻어온 녀석으로 바꿔준다.
        if (DataTable.Succeeded())
        {
            m_ObjectDataTable = DataTable.Object;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("MonsterDatas Null!"));
        }
    }
    
}

const FURMonsterDataInfo* UURGameInstance::GetMonsterData(FName Name) const
{
    FURMonsterDataInfo* DataInfo = m_MonsterDataTable->FindRow<FURMonsterDataInfo>(Name, Name.ToString());

    if (!DataInfo)
    {
        return nullptr;
    }

    return DataInfo;
}

FURPlayerDataInfo* UURGameInstance::GetPlayerData(FName Name) const
{
    FURPlayerDataInfo* DataInfo = m_PlayerDataTable->FindRow<FURPlayerDataInfo>(Name, Name.ToString());

    if (!DataInfo)
    {
        return nullptr;
    }

    return DataInfo;
}

const FURItemData* UURGameInstance::GetItemData(FName Name) const
{
    FURItemData* DataInfo = m_ItemDataTable->FindRow<FURItemData>(Name, Name.ToString());

    if (!DataInfo)
    {
        return nullptr;
    }

    return DataInfo;
}

const TSubclassOf<AActor> UURGameInstance::GetGetObjectData(FName Name) const
{
    FURObjectTable* FindTable = m_ObjectDataTable->FindRow<FURObjectTable>(Name, Name.ToString());

    if (!FindTable)
    {
        return nullptr;
    }

    return FindTable->ObjectSubClass;
}

// 랜덤한 아이템을 드롭하기위한 함수
TArray<const FURItemData*> UURGameInstance::GetRandomDropData(int _Count)
{
    for (size_t i = 0; i < 100; i++)
    {
        int Right = m_Stream.RandRange(0, m_ItemRandomTableIndex.Num() - 1);
        int Left = m_Stream.RandRange(0, m_ItemRandomTableIndex.Num() - 1);

        int32 Temp = m_ItemRandomTableIndex[Right];
        m_ItemRandomTableIndex[Right] = m_ItemRandomTableIndex[Left];
        m_ItemRandomTableIndex[Left] = Temp;
    }

    TArray<const FURItemData*> ResultArr;

    for (size_t i = 0; i < _Count; i++)
    {
        int32 RandomItemIndex = m_ItemRandomTableIndex[i];

        ResultArr.Add(m_ItemDataRandomTable[RandomItemIndex]);
    }


    return ResultArr;
}

void UURGameInstance::DebugSwitch()
{
    m_DebugCheck = !m_DebugCheck;
}
