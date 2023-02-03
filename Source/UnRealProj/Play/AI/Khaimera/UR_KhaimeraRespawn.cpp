// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/Khaimera/UR_KhaimeraRespawn.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../../Controller/URAIController.h"
#include "../../Boss/UR_KhaimeraBoss.h"
#include "Global/URStructs.h"

UUR_KhaimeraRespawn::UUR_KhaimeraRespawn()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UUR_KhaimeraRespawn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	m_Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());

	m_Boss = m_Controller->GetPawn<AUR_KhaimeraBoss>();

	if (!m_Boss->GetAnimationInstance()->IsAnimMontage(KhaimeraBossAnimation::Spawn))
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UUR_KhaimeraRespawn::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FinishLatentTask(OwnerComp, ExecuteTask(OwnerComp, NodeMemory));
}
