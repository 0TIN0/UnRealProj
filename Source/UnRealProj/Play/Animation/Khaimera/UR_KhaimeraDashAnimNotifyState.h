// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UR_KhaimeraDashAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_KhaimeraDashAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	class AUR_KhaimeraBoss* m_Khaimera;
	class AActor* m_TargetActor;

protected:
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

public:
	UFUNCTION(BlueprintCallable)
	void Finished();
	
};
