// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraBerserkTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"

UUR_KhaimeraBerserkTaskNode::UUR_KhaimeraBerserkTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_KhaimeraBerserkTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_KhaimeraBoss>();

	const FURMonsterDataInfo* MonsterInfo = m_Boss->GetKhaimeraData();

	if (m_Boss->GetHPPercent() > 0.5f)
	{
		return EBTNodeResult::Succeeded;
	}

	if (!m_Boss->GetIsBerserk())
	{
		m_Boss->SetIsBerserk(true);
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::BerserkStart);
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}

    return EBTNodeResult::Succeeded;
}

void UUR_KhaimeraBerserkTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
