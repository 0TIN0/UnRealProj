// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_DeathTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_DeathTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_DeathTaskNode();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
