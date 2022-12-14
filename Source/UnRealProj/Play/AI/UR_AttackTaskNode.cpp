// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_AttackTaskNode.h"
#include "Play/Monster.h"
#include "Play/Controller/URAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"
#include "Global/UREnum.h"

UUR_AttackTaskNode::UUR_AttackTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_AttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Controller->GetPawn<AMonster>();
	const FURMonsterDataInfo* MonsterInfo = Monster->GetMonsterData();

	if (!AnimMontageJudge(Monster))
	{
		return EBTNodeResult::Failed;
	}

	if (Monster->GetUltimateHitEnable())
	{
		return EBTNodeResult::Failed;
	}

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	// 공격 범위보다 밖에 있다면 Idle로 변경한다.
	if (!Monster->GetIsRangeInTarget(TargetActor, MonsterInfo->AttRange))
	{
		return EBTNodeResult::Failed;
	}

	UAnimMontage* Montage = Monster->GetAnimationInstance()->GetAnimation(DefaultAnimation::Attack);

	if (!Montage)
	{
		Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
		return EBTNodeResult::Failed;
	}

	m_WaitTime = Montage->GetPlayLength();

	Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);

	return EBTNodeResult::Type();
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
