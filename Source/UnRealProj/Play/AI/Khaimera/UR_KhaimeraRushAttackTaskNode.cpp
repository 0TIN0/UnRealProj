// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraRushAttackTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"

UUR_KhaimeraRushAttackTaskNode::UUR_KhaimeraRushAttackTaskNode() :
	m_Enable(false)
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_KhaimeraRushAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_KhaimeraBoss>();

	const FURMonsterDataInfo* KhaimeraInfo = m_Boss->GetKhaimeraData();

	// ���� ���° ���������� �Ǵ����ش�.
	int AttackNumb = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("RandAttackNumb"));

	// 5�� �ƴ϶�� ���� ������ �ƴϴ�.
	if (AttackNumb != 6)
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

	// ���� �������� �ۿ� �ִٸ� Idle�� �����Ѵ�.
	if (!m_Boss->GetIsRangeInTarget(TargetActor, KhaimeraInfo->SkillRange))
	{
		return EBTNodeResult::Failed;
	}

	switch (m_AttackType)
	{
	case KhaimeraAttack::RushAttack:
		if (!m_Enable)
		{
			m_Enable = true;
			m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::RushAttackStart);
		}
		break;
	}

	if (m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardFastComboAttack))
	{
		return EBTNodeResult::InProgress;
	}

	m_Enable = false;

	return EBTNodeResult::Failed;
}

void UUR_KhaimeraRushAttackTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_KhaimeraRushAttackTaskNode::AnimMontageJudge(AUR_KhaimeraBoss* _Monster)
{
	if (_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack1) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack2) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack3) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack1Recovery) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack2Recovery) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack3Recovery) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardFastComboAttack) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::DashAttack) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::BerserkStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::RushAttackStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::RushAttack) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::GetUp))
	{
		return true;
	}

	return false;
}
