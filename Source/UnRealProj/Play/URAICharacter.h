// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/URCharacter.h"
#include "URAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AURAICharacter : public AURCharacter
{
	GENERATED_BODY()

public:
	AURAICharacter();

	FORCEINLINE class UBehaviorTree* GetBehaviorTree()	const
	{
		return m_BehaviorTree;
	}

	FORCEINLINE class UBlackboardData* GetBlackBoardData()	const
	{
		return m_BlackBoardData;
	}

private:
	UPROPERTY(EditAnywhere, Category = "UR AI", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* m_BehaviorTree;

	UPROPERTY(EditAnywhere, Category = "UR AI", meta = (AllowPrivateAccess = "true"))
	class UBlackboardData* m_BlackBoardData;
	
};
