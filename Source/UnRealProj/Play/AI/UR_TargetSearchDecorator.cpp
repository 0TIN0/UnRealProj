// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/AI/UR_TargetSearchDecorator.h"
#include "Play/URAIController.h"
#include "Play/Monster.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UUR_TargetSearchDecorator::UUR_TargetSearchDecorator()
{
}

bool UUR_TargetSearchDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	AURAIController* Controller = Cast<AURAIController>(OwnerComp.GetAIOwner());
	AMonster* Monster = Controller->GetPawn<AMonster>();

	if (Monster && nullptr != Monster->TargetSearch(FName(TEXT("Player"))))
	{
		return true;
	}

	return false;
}
