// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Global/UREnum.h"
#include "UR_MoveTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_MoveTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_MoveTaskNode();

private:
	PirateAttack_Type m_AttackType;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool AnimMontageJudge(class AMonster* _Monster);
	
};
