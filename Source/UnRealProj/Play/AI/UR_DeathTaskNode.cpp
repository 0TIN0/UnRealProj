// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_DeathTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "../Controller/URAIController.h"

UUR_DeathTaskNode::UUR_DeathTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_DeathTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AMonster* Monster = Controller->GetPawn<AMonster>();

	if (Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::DeathLoop) ||
		Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::DeathStart))
	{
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Succeeded;
}

void UUR_DeathTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
