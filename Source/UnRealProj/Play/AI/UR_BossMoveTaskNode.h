// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_BossMoveTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_BossMoveTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_BossMoveTaskNode();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
