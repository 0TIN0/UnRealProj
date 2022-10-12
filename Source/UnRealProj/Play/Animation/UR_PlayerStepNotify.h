// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "UR_PlayerStepNotify.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_PlayerStepNotify : public UAnimNotify_PlaySound
{
	GENERATED_BODY()

public:
	UUR_PlayerStepNotify();
		
protected:
	virtual FString GetNotifyName_Implementation() const override;
	UE_DEPRECATED(5.0, "Please use the other Notify function instead")
		virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
#if WITH_EDITOR
	virtual void ValidateAssociatedAssets() override;
#endif
	// End UAnimNotify interface
	
};
