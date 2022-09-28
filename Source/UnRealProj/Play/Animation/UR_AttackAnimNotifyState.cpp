// Fill out your copyright notice in the Description page of Project Settings.


#include "UR_AttackAnimNotifyState.h"

void UUR_AttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AURCharacter* Character = MeshComp->GetOwner<AURCharacter>();

	if (!Character || !Character->IsValidLowLevel())
	{
		return;
	}

	Character->GetAnimationInstance()->SetMinAnimationPercent(m_MinAnimationPercent);
	Character->AttackOn();

	UE_LOG(LogTemp, Error, TEXT("Attack Start!"));
}

void UUR_AttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UUR_AttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AURCharacter* Character = MeshComp->GetOwner<AURCharacter>();

	if (!Character || !Character->IsValidLowLevel())
	{
		return;
	}

	Character->AttackOff();

	if (m_EndChangeAnimation == DefaultAnimation::Default)
	{
		return;
	}

	Character->GetAnimationInstance()->ChangeAnimMontage(m_EndChangeAnimation);
}
