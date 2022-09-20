// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_AttackTaskNode.h"
#include "Play/Monster.h"
#include "Play/URAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"

UUR_AttackTaskNode::UUR_AttackTaskNode()
{
	// TickTask�Լ��� ���۽�ų�� �������� ����
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_AttackTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Controller->GetPawn<AMonster>();
	const FURMonsterDataInfo* MonsterInfo = Monster->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FName("TargetActor"));

	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	// ���� �������� �ۿ� �ִٸ� Idle�� �����Ѵ�.
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
	// Waittime���� �� ��Ÿ���� ���̰� ���ְ�
	m_WaitTime -= DeltaSeconds;

	if (0.0f < m_WaitTime)
	{
		return;
	}

	// �׸�ŭ ��ٷȴٴ� �̾߱Ⱑ �˴ϴ�.
	m_WaitTime = 0.0f;

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
