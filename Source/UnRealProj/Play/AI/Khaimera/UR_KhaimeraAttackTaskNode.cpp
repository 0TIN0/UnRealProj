// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraAttackTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../WarriorCharacter.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"

UUR_KhaimeraAttackTaskNode::UUR_KhaimeraAttackTaskNode()	:
	m_Enable(false)
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

	if (!m_Player)
		m_Player = m_Boss->GetWorld()->GetFirstPlayerController()->GetPawn<AWarriorCharacter>();


	const FURMonsterDataInfo* KhaimeraInfo = m_Boss->GetKhaimeraData();

	// 먼저 몇번째 공격인지를 판단해준다.
	int AttackNumb = OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("RandAttackNumb"));

	// 3번공격보다 높은 공격이라는것은 다음 자손으로 넘어가야한다는 의미이다.
	if (AttackNumb > 4)
	{
		return EBTNodeResult::Succeeded;
	}

	if (AnimMontageJudge())
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

	if (!m_Enable)
	{
		if (!m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack1) &&
			!m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack2) &&
			!m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack3) &&
			!m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardCombo1))
		{
			// 공격 범위보다 밖에 있다면 Idle로 변경한다.
			// 플레이어가 넉다운 당하게되면 공격범위보다 벗어나기 때문에 해당 부분을 예외처리
			if (!m_Player->GetAnimationInstance()->IsAnimMontage(WarriorHitAnimation::CombatHitLargeToFallDown) &&
				!m_Player->GetAnimationInstance()->IsAnimMontage(WarriorHitAnimation::HitLargeToFallDown))
			{
				if (!m_Boss->GetIsRangeInTarget(TargetActor, KhaimeraInfo->AttRange))
				{
					return EBTNodeResult::Failed;
				}
			}
		}
	}

	switch (m_AttackType)
	{
	case KhaimeraAttack::Attack1:
		if (!m_Enable)
		{
			m_Enable = true;
			m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::FowardAttack1);
		}
		break;
	case KhaimeraAttack::Attack2:
		if (!m_Enable)
		{
			m_Enable = true;
			m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::FowardAttack2);
		}
		break;
	case KhaimeraAttack::Attack3:
		if (!m_Enable)
		{
			m_Enable = true;
			m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::FowardAttack3);
		}
		break;
	case KhaimeraAttack::Combo1:
		if (!m_Enable)
		{
			m_Enable = true;
			m_Boss->GetAnimationInstance()->ChangeAnimMontage(KhaimeraBossAnimation::FowardCombo1);
		}
		break;
	}

	if (m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack1) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack2) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::FowardAttack3) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack1Recovery) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack2Recovery) ||
		m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Attack3Recovery))
	{
		return EBTNodeResult::InProgress;
	}

	m_Enable = false;

	return EBTNodeResult::Succeeded;
}

void UUR_KhaimeraAttackTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}

bool UUR_KhaimeraAttackTaskNode::AnimMontageJudge()
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
