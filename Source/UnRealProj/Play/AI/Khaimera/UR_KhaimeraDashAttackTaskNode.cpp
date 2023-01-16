// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraDashAttackTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"

UUR_KhaimeraDashAttackTaskNode::UUR_KhaimeraDashAttackTaskNode()	:
	m_Enable(false)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_KhaimeraDashAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_KhaimeraBoss>();

	const FURMonsterDataInfo* KhaimeraInfo = m_Boss->GetKhaimeraData();
	
	// 먼저 몇번째 공격인지를 판단해준다.
	int AttackNumb = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("RandAttackNumb"));

	// 5가 아니라면 데쉬 어택이 아니다.
	if (AttackNumb != 5)
	{
		return EBTNodeResult::Succeeded;
	}
	
	m_AttackType = static_cast<KhaimeraAttack>(AttackNumb);

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	// 공격 범위보다 밖에 있다면 Idle로 변경한다.
	if (!m_Boss->GetIsRangeInTarget(TargetActor, KhaimeraInfo->SkillRange))
	{
		return EBTNodeResult::Failed;
	}

	switch (m_AttackType)
	{
	case KhaimeraAttack::DashAttack:
		if (!m_Enable)
		{
			m_Enable = true;
			m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::DashStart);
		}
		break;
	}

	if (m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashStart) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashAttack))
	{
		return EBTNodeResult::InProgress;
	}

	m_Enable = false;

	return EBTNodeResult::Failed;
}

void UUR_KhaimeraDashAttackTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_KhaimeraDashAttackTaskNode::AnimMontageJudge()
{
	if (m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack1) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack2) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack3) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack1Recovery) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack2Recovery) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack3Recovery) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardFastComboAttack) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashStart) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashAttack) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::BerserkStart) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::RushAttackStart) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::RushAttack) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
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
