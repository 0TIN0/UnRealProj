// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_DashEndAnimNotifyState.h"
#include "../WarriorCharacter.h"

void UUR_DashEndAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AWarriorCharacter* Player = Cast<AWarriorCharacter>(MeshComp->GetOwner());

	if (!Player || !Player->IsValidLowLevel())
	{
		return;
	}


	if (Player->GetRightDown() && !Player->GetForwardDown() && !Player->GetLeftDown() && !Player->GetBackwardDown())
	{
		if (Player->GetCtrlDown())
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Right);
		}
		else
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Right);
		}
	}
	else if (Player->GetLeftDown() && !Player->GetForwardDown() && !Player->GetRightDown() && !Player->GetBackwardDown())
	{
		if (Player->GetCtrlDown())
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Left);
		}
		else
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Left);
		}
	}
	else if (Player->GetForwardDown() && !Player->GetLeftDown() && !Player->GetRightDown() && !Player->GetBackwardDown())
	{
		if (Player->GetCtrlDown())
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);
		}
		else
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);
		}
	}
	else if (Player->GetBackwardDown() && !Player->GetForwardDown() && !Player->GetRightDown() && !Player->GetLeftDown())
	{
		if (Player->GetCtrlDown())
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::BackWard);
		}
		else
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::BackWard);
		}
	}
	else if (Player->GetRightDown() && Player->GetForwardDown() && !Player->GetLeftDown() && !Player->GetBackwardDown())
	{
		if (Player->GetCtrlDown())
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::ForWardRight);
		}
		else
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::ForWardRight);
		}
	}
	else if (Player->GetLeftDown() && Player->GetForwardDown() && !Player->GetRightDown() && !Player->GetBackwardDown())
	{
		if (Player->GetCtrlDown())
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::ForWardLeft);
		}
		else
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::ForWardLeft);
		}
	}
	else if (Player->GetRightDown() && Player->GetBackwardDown() && !Player->GetLeftDown() && !Player->GetForwardDown())
	{
		if (Player->GetCtrlDown())
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::BackWardRight);
		}
		else
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::BackWardRight);
		}
	}
	else if (Player->GetLeftDown() && Player->GetBackwardDown() && !Player->GetRightDown() && !Player->GetForwardDown())
	{
		if (Player->GetCtrlDown())
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::BackWardLeft);
		}
		else
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::BackWardLeft);
		}
	}
	else
	{
		if (Player->GetIsCombating())
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatIdle);
		}
		else
		{
			Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
		}
	}
}
