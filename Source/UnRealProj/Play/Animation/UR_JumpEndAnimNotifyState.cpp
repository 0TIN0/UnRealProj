// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_JumpEndAnimNotifyState.h"
#include "../PlayCharacter.h"
#include "../WarriorCharacter.h"

void UUR_JumpEndAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	switch (m_PlayerType)
	{
	case UPLAYER_TYPE::Wizard:
	{
		/*DefaultAnimation Anim = DefaultAnimation::Idle;
		ChnageAnimMontage<APlayCharacter, DefaultAnimation>(MeshComp, Anim);*/
	}
	break;
	case UPLAYER_TYPE::Warrior:
	{
		AWarriorCharacter* Character = MeshComp->GetOwner<AWarriorCharacter>();

		if (!Character || !Character->IsValidLowLevel())
		{
			return;
		}

		Character->AttackOff();

		if (Character->GetIsCombating())
		{
			Character->SetIsJumping(false);
			WarriorCombatAnimation Anim = WarriorCombatAnimation::CombatIdle;
			Character->GetAnimationInstance()->ChangeAnimMontage(Anim);
		}
		else
		{
			Character->SetIsJumping(false);
			DefaultAnimation Anim = DefaultAnimation::Idle;
			Character->GetAnimationInstance()->ChangeAnimMontage(Anim);
		}
	}
	break;
	}
}
