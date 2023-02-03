// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UR_BlockingMoveTaskNode.generated.h"

UENUM(BlueprintType)
enum class PathPos_Type	: uint8
{
	Default,
	Left,
	Right,
	Backward
};

UCLASS()
class UNREALPROJ_API UUR_BlockingMoveTaskNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UUR_BlockingMoveTaskNode();

private:
	PathPos_Type m_Type;

	bool m_Enable;


protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
