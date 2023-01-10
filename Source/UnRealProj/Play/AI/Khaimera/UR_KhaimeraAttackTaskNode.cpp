// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraAttackTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"

UUR_KhaimeraAttackTaskNode::UUR_KhaimeraAttackTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_KhaimeraAttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!m_Controller)
		m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	if (!m_Boss)
		m_Boss = m_Controller->GetPawn<AUR_KhaimeraBoss>();

	const FURMonsterDataInfo* KhaimeraInfo = m_Boss->GetKhaimeraData();

	// 먼저 몇번째 공격인지를 판단해준다.
	int AttackNumb = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("RandAttackNumb"));

	// 3번공격보다 높은 공격이라는것은 다음 자손으로 넘어가야한다는 의미이다.
	if (AttackNumb > 3)
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
	if (!m_Boss->GetIsRangeInTarget(TargetActor, KhaimeraInfo->AttRange))
	{
		return EBTNodeResult::Succeeded;
	}

	if (AnimMontageJudge(m_Boss))
	{
		return EBTNodeResult::Succeeded;
	}

	switch (m_AttackType)
	{
	case KhaimeraAttack::Attack1:
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::FowardAttack1);
		break;
	case KhaimeraAttack::Attack2:
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::FowardAttack2);
		break;
	case KhaimeraAttack::Attack3:
		m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::FowardAttack3);
		break;
	}

	return EBTNodeResult::Succeeded;
}

void UUR_KhaimeraAttackTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_KhaimeraAttackTaskNode::AnimMontageJudge(AUR_KhaimeraBoss* _Monster)
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
