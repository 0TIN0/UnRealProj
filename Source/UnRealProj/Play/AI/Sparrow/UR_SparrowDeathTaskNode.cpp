// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Sparrow/UR_SparrowDeathTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_SparrowSubBoss.h"
#include "Global/URStructs.h"

UUR_SparrowDeathTaskNode::UUR_SparrowDeathTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_SparrowDeathTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_SparrowSubBoss>();

	// 스페로우의 HP가 0보다 크다면 패스한다.
	if (m_Boss->GetHP() > 0.0)
	{
		return EBTNodeResult::Failed;
	}

	if (m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ExecutionTarget))
	{
		return EBTNodeResult::InProgress;
		m_Boss->SetIsInvincibility(true);
	}
	// 여기에 왔다면 죽은것이기 떄문에 해당 동작을 실행해주고 InProgress로 유지시켜준다.
	if (!m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::DeathStart))
	{
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::DeathLoop);
		m_Boss->SetIsInvincibility(true);
	}

	return EBTNodeResult::InProgress;
}

void UUR_SparrowDeathTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
