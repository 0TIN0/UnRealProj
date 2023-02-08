// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_AttackTaskNode.h"
#include "Play/Monster.h"
#include "Play/Controller/URAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"

UUR_AttackTaskNode::UUR_AttackTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_AttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	m_Monster = m_Controller->GetPawn<AMonster>();

	const FURMonsterDataInfo* MonsterInfo = m_Monster->GetMonsterData();

	if (m_Monster->IsDeath())
	{
		return EBTNodeResult::Failed;
	}
	if (!AnimMontageJudge(m_Monster))
	{
		return EBTNodeResult::Failed;
	}

	if (m_Monster->GetUltimateHitEnable())
	{
		return EBTNodeResult::Failed;
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	// 몬스터가 블로킹중이라면 블로킹중을 false변경했다 알려주어야함.
	if (m_Monster->GetIsBlocking())
		m_Monster->SetIsBlocking(false);

	AActor* TargetActor = Cast<AActor>(Target);

	m_AttackType = static_cast<PirateAttack_Type>(OwnerComp.GetBlackboardComponent()->GetValueAsInt(FName("RandAttackNumb")));

	switch (m_AttackType)
	{
	case PirateAttack_Type::Attack:
	case PirateAttack_Type::AttackCombo1:
		// 공격 범위보다 밖에 있다면 Idle로 변경한다.
		if (!m_Monster->GetIsRangeInTarget(TargetActor, MonsterInfo->AttRange))
		{
			return EBTNodeResult::Failed;
		}
		break;
	case PirateAttack_Type::AttackCombo2:
		// 공격 범위보다 밖에 있다면 Idle로 변경한다.
		if (!m_Monster->GetIsRangeInTarget(TargetActor, MonsterInfo->AttRange + 200.f))
		{
			return EBTNodeResult::Failed;
		}
		break;
	}
	//// 공격 범위보다 밖에 있다면 Idle로 변경한다.
	//if (!m_Monster->GetIsRangeInTarget(TargetActor, MonsterInfo->AttRange))
	//{
	//	return EBTNodeResult::Failed;
	//}

	UAnimMontage* Montage = m_Monster->GetAnimationInstance()->GetAnimation(DefaultAnimation::Attack);

	if (!Montage)
	{
		m_Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
		return EBTNodeResult::Failed;
	}

	m_WaitTime = Montage->GetPlayLength();

	if (!m_Monster->GetAIStruct().IsAttack)
	{
		switch (m_AttackType)
		{
		case PirateAttack_Type::Attack:
			m_Monster->SetAIIsAttack(true);
			m_Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
			break;
		case PirateAttack_Type::AttackCombo1:
			m_Monster->SetAIIsAttack(true);
			m_Monster->GetAnimationInstance()->ChangeAnimMontage(PirateAnimation::AttackCombo1);
			break;
		case PirateAttack_Type::AttackCombo2:
			m_Monster->SetAIIsAttack(true);
			m_Monster->GetAnimationInstance()->ChangeAnimMontage(PirateAnimation::AttackCombo2);
			break;
		}
	}

	if (m_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::Attack) ||
		m_Monster->GetAnimationInstance()->IsAnimMontage(PirateAnimation::AttackCombo1) ||
		m_Monster->GetAnimationInstance()->IsAnimMontage(PirateAnimation::AttackCombo2))
	{
		return EBTNodeResult::InProgress;
	}


	m_Monster->SetAIIsAttack(false);

	return EBTNodeResult::Failed;
}

void UUR_AttackTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Waittime에는 이 몽타주의 길이가 들어가있고
	m_WaitTime -= DeltaSeconds;

	if (0.0f < m_WaitTime)
	{
		return;
	}

	// 그만큼 기다렸다는 이야기가 됩니다.
	m_WaitTime = 0.0f;

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

bool UUR_AttackTaskNode::AnimMontageJudge(class AMonster* _Monster)
{
	if (_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::GetUp) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirToFloorStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirToFloorEnd) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::DeathStart) ||
		_Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::DeathLoop))
	{
		return false;
	}

	return true;
}
