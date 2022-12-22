// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_KrakenAttackTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_KrakenAttackTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_KrakenAttackTaskNode();

private:
	float m_WaitTime;
	class AURAIController* m_Controller;
	class AUR_KrakenBoss* m_Boss;
	FRandomStream m_Stream; // 난수 생성기.

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
