// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UR_MotionWarpingDash.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_MotionWarpingDash : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	class AWarriorCharacter* m_Player;
	class AActor* m_TargetActor;

protected:
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

private:
	void Finished();
	
};
