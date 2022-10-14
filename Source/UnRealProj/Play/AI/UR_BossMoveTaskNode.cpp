// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_BossMoveTaskNode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../UR_BossMonster.h"
#include "Play/Controller/URAIController.h"
#include "Global/URStructs.h"
#include "Global/URBlueprintFunctionLibrary.h"

UUR_BossMoveTaskNode::UUR_BossMoveTaskNode()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_BossMoveTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AUR_BossMonster* Boss = Controller->GetPawn<AUR_BossMonster>();
	const FURMonsterDataInfo* MonsterInfo = Boss->GetMonsterData();

	UObject* Target = OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor");

	if (!Target)
	{
		return EBTNodeResult::Succeeded;
	}

	AActor* TargetActor = Cast<AActor>(Target);

	FVector Dir = TargetActor->GetActorLocation() - Boss->GetActorLocation();

	if (Boss->GetTargetDir(TargetActor).Size() < MonsterInfo->SkillRange)
	{
		//Monster->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
		return EBTNodeResult::Failed;
	}


	Boss->SetTargetLook(TargetActor);
	Boss->SetTargetMovementInput(TargetActor);
	Boss->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);


	return EBTNodeResult::Type::InProgress;
}

void UUR_BossMoveTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
