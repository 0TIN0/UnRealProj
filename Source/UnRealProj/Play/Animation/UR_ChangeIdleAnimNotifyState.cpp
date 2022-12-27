// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_ChangeIdleAnimNotifyState.h"
#include "../PlayCharacter.h"
#include "../WarriorCharacter.h"

void UUR_ChangeIdleAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	switch (m_PlayerType)
	{
	case UPLAYER_TYPE::Wizard:
	{
	}
	break;
	case UPLAYER_TYPE::Warrior:
	{
		AWarriorCharacter* Character = MeshComp->GetOwner<AWarriorCharacter>();

		if (!Character || !Character->IsValidLowLevel())
		{
			return;
		}

		if (!Character->GetIsCombating())
		{
			Character->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
		}
		else
		{
			Character->GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatIdle);
		}
	}
	break;
	}
}
