// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_BossFireBallTaskNode.h"
#include "../Play/UR_BossMonster.h"
#include "Play/Controller/URAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"

UUR_BossFireBallTaskNode::UUR_BossFireBallTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_BossFireBallTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AUR_BossMonster* Boss = Controller->GetPawn<AUR_BossMonster>();
	const FURMonsterDataInfo* MonsterInfo = Boss->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	// 공격 범위보다 밖에 있다면 Idle로 변경한다.
	if (!Boss->GetIsRangeInTarget(TargetActor, MonsterInfo->SkillRange))
	{
		return EBTNodeResult::Failed;
	}

	UAnimMontage* Montage = Boss->GetAnimationInstance()->GetCurrentMontage();

	/*if (Montage->GetName() == FString(TEXT("UR_Lich_Attack_Right_Montage")))
	{
		return EBTNodeResult::Failed;
	}*/

	if (!Boss->GetIsRangeInTarget(TargetActor, MonsterInfo->SkillRange))
	{
		return EBTNodeResult::Failed;
	}

	m_WaitTime = Montage->GetPlayLength();

	Boss->GetAnimationInstance()->ChangeAnimMontage(BossAnimation::Skill1);

	return EBTNodeResult::InProgress;
}

void UUR_BossFireBallTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
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
