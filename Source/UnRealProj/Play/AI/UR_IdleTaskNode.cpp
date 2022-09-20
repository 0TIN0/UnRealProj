// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_IdleTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "Play/URAIController.h"

UUR_IdleTaskNode::UUR_IdleTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_IdleTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AMonster* Monster = Controller->GetPawn<AMonster>();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (Target)
	{
		return EBTNodeResult::Failed;
	}

	Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);

	return EBTNodeResult::InProgress;
}

void UUR_IdleTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
