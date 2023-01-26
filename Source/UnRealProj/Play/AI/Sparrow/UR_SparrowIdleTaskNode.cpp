// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Sparrow/UR_SparrowIdleTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_SparrowSubBoss.h"
#include "Global/URStructs.h"

UUR_SparrowIdleTaskNode::UUR_SparrowIdleTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_SparrowIdleTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_SparrowSubBoss>();

	const FURMonsterDataInfo* MonsterInfo = m_Boss->GetSparrowData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (Target)
	{
		return EBTNodeResult::Failed;
	}

	m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);

	return EBTNodeResult::InProgress;
}

void UUR_SparrowIdleTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

bool UUR_SparrowIdleTaskNode::AnimMontageJudge()
{
	if (m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::GetUp))
	{
		return true;
	}

	return false;
}
