// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/AnimNotify/UR_HitSoundNotify.h"

UUR_HitSoundNotify::UUR_HitSoundNotify()	:
	m_PlayerType(UPLAYER_TYPE::Default),
	m_MonsterType(UMONSTER_TYPE::Default)
{
	static ConstructorHelpers::FObjectFinder<USoundBase> WarriorHit(TEXT("SoundCue'/Game/Resource/Play/Sound/Voice/Kwang/Kwang_Effort_Pain.Kwang_Effort_Pain'"));

	if (WarriorHit.Succeeded())
		m_WarriorHit = WarriorHit.Object;
	else
		UE_LOG(LogTemp, Error, TEXT("WarriorHit Sound Null!"));

	// ��� Ÿ���� ���̶�� ������ �� ���ذ��̱� ������ Log����־� ����
	if ((m_PlayerType == UPLAYER_TYPE::Default) && (m_MonsterType == UMONSTER_TYPE::Default))
	{
		UE_LOG(LogTemp, Error, TEXT("HitSoundNotify All Type Default!"));
	}

	VolumeMultiplier = 0.2f;
}

void UUR_HitSoundNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	//��Ƽ���̸� �����ϱ����� ��Ƽ���̿� ������ ���带 �������ش�.
	switch (m_PlayerType)
	{
	case UPLAYER_TYPE::Wizard:
		break;
	case UPLAYER_TYPE::Warrior:
		Sound = m_WarriorHit;
		break;
	}

	switch (m_MonsterType)
	{
	case UMONSTER_TYPE::Pirate:
		break;
	case UMONSTER_TYPE::Khaimera:
		break;
	case UMONSTER_TYPE::Sparrow:
		break;
	}
	Super::Notify(MeshComp, Animation, EventReference);
}
