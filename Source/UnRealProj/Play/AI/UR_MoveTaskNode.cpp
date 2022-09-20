// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_MoveTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Play/Monster.h"
#include "Play/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"

UUR_MoveTaskNode::UUR_MoveTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_MoveTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Controller->GetPawn<AMonster>();
	const FURMonsterDataInfo* MonsterInfo = Monster->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (!Target)
	{
		return EBTNodeResult::Succeeded;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	FVector Dir = TargetActor->GetActorLocation() - Monster->GetActorLocation();

	if (Monster->GetTargetDir(TargetActor).Size() < MonsterInfo->AttRange)
	{
		//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
		return EBTNodeResult::Failed;
	}


	Monster->SetTargetLook(TargetActor);
	Monster->SetTargetMovementInput(TargetActor);
	Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);


	return EBTNodeResult::Type::InProgress;
}

void UUR_MoveTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
