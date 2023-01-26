// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_SparrowRandAttackJudge.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_SparrowRandAttackJudge : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_SparrowRandAttackJudge();

private:
	FRandomStream m_Stream;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
