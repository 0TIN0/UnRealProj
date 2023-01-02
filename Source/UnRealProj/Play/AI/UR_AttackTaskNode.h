// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_AttackTaskNode.generated.h"

UCLASS()
class UNREALPROJ_API UUR_AttackTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_AttackTaskNode();

private:
	float m_WaitTime;
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool AnimMontageJudge(class AMonster* _Monster);
};
