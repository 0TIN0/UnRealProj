// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraIdleTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"

UUR_KhaimeraIdleTaskNode::UUR_KhaimeraIdleTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_KhaimeraIdleTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_KhaimeraBoss>();
	
	const FURMonsterDataInfo* MonsterInfo = m_Boss->GetKhaimeraData();


	if (AnimMontageJudge(m_Boss))
	{
		return EBTNodeResult::Failed;
	}


	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (Target)
	{
		return EBTNodeResult::Failed;
	}

	m_Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);

	return EBTNodeResult::InProgress;
}

void UUR_KhaimeraIdleTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_KhaimeraIdleTaskNode::AnimMontageJudge(AUR_KhaimeraBoss* _Monster)
{
	if (_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack1) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack2) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack3) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack1Recovery) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack2Recovery) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack3Recovery) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashAttack) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop))
	{
		return true;
	}

	return false;
}
