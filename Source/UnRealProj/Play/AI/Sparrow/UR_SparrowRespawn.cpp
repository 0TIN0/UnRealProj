// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Sparrow/UR_SparrowRespawn.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_SparrowSubBoss.h"
#include "Global/URStructs.h"

UUR_SparrowRespawn::UUR_SparrowRespawn()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_SparrowRespawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	AUR_SparrowSubBoss* Boss = Controller->GetPawn<AUR_SparrowSubBoss>();

	if (!Boss->GetAnimationInstance()->IsAnimMontage(SparrowBossAnimation::Spawn))
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UUR_SparrowRespawn::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
