// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_KhaimeraDeathTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_KhaimeraDeathTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_KhaimeraDeathTaskNode();

private:
	class AURAIController* m_Controller;
	class AUR_KhaimeraBoss* m_Boss;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
