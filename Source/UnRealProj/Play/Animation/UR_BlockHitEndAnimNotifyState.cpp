// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_BlockHitEndAnimNotifyState.h"
#include "../WarriorCharacter.h"
#include "../URCharacter.h"

void UUR_BlockHitEndAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	switch (m_MonsterType)
	{
	case UMONSTER_TYPE::Pirate:
	{
		AURCharacter* Character = MeshComp->GetOwner<AURCharacter>();

		if (!Character || !Character->IsValidLowLevel())
		{
			return;
		}
	}
	break;
	}

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

		if (Character->GetIsBlocking())
		{
			Character->GetAnimationInstance()->ChangeAnimMontage(WarriorBlockAnimation::BlockLoop);
		}
		else
		{
			if (!Character->GetIsCombating())
			{
				Character->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
			}
			else
			{
				Character->GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatIdle);
			}
		}
	}
	break;
	}
}
