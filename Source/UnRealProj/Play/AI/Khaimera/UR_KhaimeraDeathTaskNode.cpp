// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraDeathTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"

UUR_KhaimeraDeathTaskNode::UUR_KhaimeraDeathTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_KhaimeraDeathTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_KhaimeraBoss>();

	if (m_Boss->GetHP() > 0.0)
	{
		return EBTNodeResult::Succeeded;
	}

	if (!m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::DeathStart))
	{
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::DeathLoop);
		m_Boss->SetIsInvincibility(true);
	}

	return EBTNodeResult::InProgress;
}

void UUR_KhaimeraDeathTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
