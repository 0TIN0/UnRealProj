// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_SparrowDeathTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_SparrowDeathTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_SparrowDeathTaskNode();

private:
	class AURAIController* m_Controller;
	class AUR_SparrowSubBoss* m_Boss;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
