// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "UR_FootStepSoundNotify.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_FootStepSoundNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	UUR_FootStepSoundNotify();

	EPhysicalSurface m_StepSurface;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		USoundBase* m_Modern;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		USoundBase* m_Dirty;


protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	

private:
	void SelectSoundBase(class USoundBase** _SoundBase);
};
