// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "Global/URBlueprintFunctionLibrary.h"

void AMonster::BeginPlay()
{
	Super::BeginPlay();

	m_MonsterData = UURBlueprintFunctionLibrary::GetURInst()->GetMonsterData(m_MonsterStatusKey);

	if (!m_MonsterData)
	{
		UE_LOG(LogTemp, Error, TEXT("MonterData Empty"));
	}
}
