// Fill out your copyright notice in the Description page of Project Settings.


#include "UR_DamageAnimNotifyState.h"
#include "../URCharacter.h"

void UUR_DamageAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	AURCharacter* Actor = MeshComp->GetOwner<AURCharacter>();

	if (!Actor || !Actor->IsValidLowLevel())
	{
		return;
	}


	Actor->SetKnockDown(m_IsKnockDown);
	Actor->DamageOn();

	if (!Actor->GetAnimationInstance()->IsAnimMontage(WarriorAnimation::SkillELoop))
		Actor->CameraShake(CameraShake_Type::HitShake);

	m_OneFrame = false;
}

void UUR_DamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	AURCharacter* Actor = MeshComp->GetOwner<AURCharacter>();

	if (!Actor || !Actor->IsValidLowLevel())
	{
		return;
	}

	// begin이랑 tick간 1프레임이 존재해야하는데 없으므로
	// 1프레임은 그냥 지나가고 코드가 실행되도록 시킨다.
	if (!m_OneFrame)
	{
		m_OneFrame = true;
		return;
	}

	Actor->DamageOff();
}

void UUR_DamageAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
}
