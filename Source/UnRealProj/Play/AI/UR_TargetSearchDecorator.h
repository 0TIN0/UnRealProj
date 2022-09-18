// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "UR_TargetSearchDecorator.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_TargetSearchDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
	UUR_TargetSearchDecorator();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
