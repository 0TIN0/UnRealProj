// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_AttackEndAnimNotifyState.h"
#include "../PlayCharacter.h"
#include "../WarriorCharacter.h"

void UUR_AttackEndAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	switch (m_PlayerType)
	{
	case UPLAYER_TYPE::Wizard:
	{
		DefaultAnimation Anim = DefaultAnimation::Idle;
		ChnageAnimMontage<APlayCharacter, DefaultAnimation>(MeshComp, Anim);
	}
		break;
	case UPLAYER_TYPE::Warrior:
	{
		WarriorCombatAnimation Anim = WarriorCombatAnimation::CombatIdle;
		ChnageAnimMontage<AWarriorCharacter, WarriorCombatAnimation>(MeshComp, Anim);
	}
		break;
	}
}
