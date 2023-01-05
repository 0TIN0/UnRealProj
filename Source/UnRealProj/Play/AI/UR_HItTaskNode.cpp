// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_HItTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "../Controller/URAIController.h"

UUR_HItTaskNode::UUR_HItTaskNode()
{
	// TickTask함수를 동작시킬지 결정해주 변수
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_HItTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AMonster* Monster = Controller->GetPawn<AMonster>();

	if (Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::KnockDown) ||
		Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop) ||
		Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirToFloorEnd) ||
		Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirToFloorStart) ||
		Monster->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::GetUp))
	{
		return EBTNodeResult::InProgress;
	}



	return EBTNodeResult::Succeeded;
}

void UUR_HItTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
