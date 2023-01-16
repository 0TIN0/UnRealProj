// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraRandAttackJudge.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"
#include "Global/URGameInstance.h"

UUR_KhaimeraRandAttackJudge::UUR_KhaimeraRandAttackJudge()	:
	m_Stream(FRandomStream(FDateTime::Now().GetTicks()))
{
}

EBTNodeResult::Type UUR_KhaimeraRandAttackJudge::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	//// 어떤 공격을 할지 정해주는 TaskNode이다.
	//if (!m_Controller)
	//	m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	//if (!m_Boss)
	//	m_Boss = m_Controller->GetPawn<AUR_KhaimeraBoss>();

	int32 RandAttackNumb = (int32)m_Stream.FRandRange(1, 6);

	OwnerComp.GetBlackboardComponent()->SetValueAsInt(FName("RandAttackNumb"), RandAttackNumb);

	return EBTNodeResult::Failed;
}
