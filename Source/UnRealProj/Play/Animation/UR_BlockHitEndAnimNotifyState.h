// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Global/UREnum.h"
#include "UR_BlockHitEndAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_BlockHitEndAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		UPLAYER_TYPE m_PlayerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		UMONSTER_TYPE m_MonsterType;

protected:
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
