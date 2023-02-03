// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_TurnTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_TurnTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_TurnTaskNode();

private:
	class AURAIController* m_Controller;
	class AURCharacter* m_Monster;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	virtual bool AnimMontageJudge();
};
