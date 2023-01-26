// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UR_RainShootCreateDecal.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_RainShootCreateDecal : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	
};
