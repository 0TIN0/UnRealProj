// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UR_PostProcessOnOff.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_PostProcessOnOff : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	class AWarriorCharacter* m_Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		bool m_IsOnOff;

protected:
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	
};
