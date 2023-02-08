// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Sparrow/UR_SparrowHitTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_SparrowSubBoss.h"
#include "Global/URStructs.h"

UUR_SparrowHitTaskNode::UUR_SparrowHitTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_SparrowHitTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AUR_SparrowSubBoss* Boss = Controller->GetPawn<AUR_SparrowSubBoss>();

	if (Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::ForwardHit) ||
		Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackwardHit) ||
		Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::LeftHit) ||
		Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::RightHit) ||
		Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirLoop) ||
		Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirToFloorStart) ||
		Boss->GetAnimationInstance()->IsAnimMontage(DefaultAnimation::HitAirToFloorEnd))
	{
		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Succeeded;
}

void UUR_SparrowHitTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
