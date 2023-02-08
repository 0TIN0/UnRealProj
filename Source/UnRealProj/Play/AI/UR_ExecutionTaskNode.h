// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_ExecutionTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_ExecutionTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_ExecutionTaskNode();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
