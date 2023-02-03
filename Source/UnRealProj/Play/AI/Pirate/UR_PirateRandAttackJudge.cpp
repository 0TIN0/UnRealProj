// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Pirate/UR_PirateRandAttackJudge.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UUR_PirateRandAttackJudge::UUR_PirateRandAttackJudge() :
	m_Stream(FRandomStream(FDateTime::Now().GetTicks()))
{
}

EBTNodeResult::Type UUR_PirateRandAttackJudge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	// 어떤 공격을 할지 정해주는 TaskNode이다.
	int32 RandAttackNumb = (int32)m_Stream.FRandRange(1.0, 3.99999);

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("RandAttackNumb"), RandAttackNumb);

	return EBTNodeResult::Failed;
}
