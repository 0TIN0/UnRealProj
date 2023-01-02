// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_ChangeAnimNotifyState.h"
#include "../URCharacter.h"
#include "URAnimInstance.h"

void UUR_ChangeAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AURCharacter* Character = MeshComp->GetOwner<AURCharacter>();

	if (!Character || !Character->IsValidLowLevel())
	{
		return;
	}

	//Character->GetAnimationInstance()->ChangeAnimMontage(m_ChangeAnimation);
	//Character->GetAnimationInstance()->Montage_Play(m_ChangeAnimation);
	int Key = Character->GetAnimationInstance()->FindMontageKey(m_ChangeAnimation);
	Character->GetAnimationInstance()->ChangeAnimMontage(Key);
	Character->SetHitType(m_HitType);
}
