// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_SparrowRainAttack.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_SparrowRainAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_SparrowRainAttack();

private:
	class AURAIController* m_Controller;
	class AUR_SparrowSubBoss* m_Boss;
	class AWarriorCharacter* m_Player;

	bool m_Enable;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool AnimMontageJudge();
	
};
