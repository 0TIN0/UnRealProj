// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Global/UREnum.h"
#include "UR_ChangeAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_ChangeAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		class UAnimMontage* m_ChangeAnimation;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		EHitType m_HitType;


protected:
	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
};
