// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UR_ExecutionEndNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_ExecutionEndNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	class AWarriorCharacter* m_Player;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class AActor>	m_SpawnActorClass;

protected:
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
