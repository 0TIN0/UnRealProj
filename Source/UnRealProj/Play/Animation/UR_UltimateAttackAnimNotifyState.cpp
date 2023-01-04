// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_UltimateAttackAnimNotifyState.h"
#include "../WarriorCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void UUR_UltimateAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	m_Player = MeshComp->GetOwner<AWarriorCharacter>();

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}

	m_Player->UltimateAttack();
	
	/*FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("Finished");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = 0;

	for (auto& Target : m_Player->GetUltimateTarget())
	{
		FVector Dir = Target->GetActorLocation() - m_Player->GetActorLocation();
		Dir = Dir.GetSafeNormal();

		FVector EndPos = Target->GetActorLocation() + Dir * 500.f;

		FRotator PlayerRot = Dir.Rotation();

		m_Player->GetController()->SetControlRotation(PlayerRot);

		UKismetSystemLibrary::MoveComponentTo(m_Player->GetRootComponent(), EndPos, m_Player->GetActorRotation(),
			false, false, 0.05f, true, EMoveComponentAction::Type::Move, LatentInfo);
	}*/
}

void UUR_UltimateAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}
}

void UUR_UltimateAttackAnimNotifyState::Finished()
{
}
