// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_KhaimeraRandAttackJudge.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_KhaimeraRandAttackJudge : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_KhaimeraRandAttackJudge();

private:
	class AURAIController* m_Controller;
	class AUR_KhaimeraBoss* m_Boss;
	FRandomStream m_Stream;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
