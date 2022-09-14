// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "URMonsterController.h"

AMonster::AMonster()
{
	AIControllerClass = AURMonsterController::StaticClass();
}

const FURMonsterDataInfo* AMonster::MonsterDataInit()
{
	m_MonsterData = UURBlueprintFunctionLibrary::GetURInst()->GetMonsterData(m_MonsterStatusKey);

	if (!m_MonsterData)
	{
		UE_LOG(LogTemp, Error, TEXT("MonterData Empty"));
	}

	return m_MonsterData;
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
}
