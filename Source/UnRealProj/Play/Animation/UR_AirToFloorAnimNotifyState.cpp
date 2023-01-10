// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/UR_AirToFloorAnimNotifyState.h"
#include "../WarriorCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Object/UR_UltimateShockWave.h"
#include "../Object/UR_UltimateDisCharge.h"

void UUR_AirToFloorAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	m_Player = MeshComp->GetOwner<AWarriorCharacter>();

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}

	for (auto& Target1 : m_Player->GetUltimateTarget())
	{
		if (Target1)
			Target1->GetCharacterMovement()->GravityScale = 5.f;
	}

	//m_Player->CreateParticleObject<AUR_UltimateDisCharge>(m_Player);
	m_Player->GetCharacterMovement()->GravityScale = 5.f;

	m_Player->GetWorldSettings()->SetTimeDilation(1.f);
}

void UUR_AirToFloorAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UUR_AirToFloorAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	if (!m_Player || !m_Player->IsValidLowLevel())
	{
		return;
	}



	FActorSpawnParameters spawnParams;
	FVector vecSpawnPos = m_Player->GetActorLocation();
	FTransform SpawnTransform = FTransform(vecSpawnPos);

	m_Player->GetWorld()->SpawnActor<AUR_UltimateShockWave>(AUR_UltimateShockWave::StaticClass(), SpawnTransform, spawnParams);

	m_Player->CameraShake(CameraShake_Type::UltimateShake);

	for (auto& Target : m_Player->GetUltimateTarget())
	{
		if (Target)
		{
			Target->GetCharacterMovement()->GravityScale = 2.f;
			Target->SetHitType(EHitType::KnockDownHit);
			Target->CallDamage(m_Player->GetPlayerInfo()->MaxAttack, m_Player);
		}
	}

	m_Player->GetCharacterMovement()->GravityScale = 2.f;
	m_Player->AttackOff();
	m_Player->SetIsUltimateAttack(false);
	m_Player->SetIsInvincibility(false);

	if (!m_Player->GetIsCombating())
	{
		m_Player->GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
	}
	else
	{
		m_Player->GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatIdle);
	}

	// 새로 SphereTrace로 탐색하고 아래에 있는 적들을 넉다운 시킨다
	TArray<AURCharacter*> ReTargetArray = m_Player->GetSphereTraceHitActor(100.f, 2000.f);


	for (auto& ReTarget : ReTargetArray)
	{
		if (ReTarget)
		{
			ReTarget->SetHitType(EHitType::KnockDownHit);
			ReTarget->CallDamage(m_Player->GetPlayerInfo()->MaxAttack, m_Player);
		}
	}
}
