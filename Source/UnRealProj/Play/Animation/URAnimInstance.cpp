// Fill out your copyright notice in the Description page of Project Settings.


#include "URAnimInstance.h"


UURAnimInstance::UURAnimInstance()
{
}

void UURAnimInstance::AddAnimMontage(int Key, UAnimMontage* Montage)
{
	if (m_Animations.Contains(Key))
	{
		UE_LOG(LogTemp, Error, TEXT("Animation Instance Error!"));
		return;
	}

	m_Animations.Add(Key, Montage);
}

void UURAnimInstance::ChangeAnimMontage(int Key, float _MinAnimationPercent, bool Force)
{
	UAnimMontage* FindMontage = GetAnimation(Key);

	if (Force)
	{
		m_MinAnimationPercent = _MinAnimationPercent;
		m_AnimationLen = FindMontage->GetPlayLength();
		m_AnimationTime = 0.0f;
		m_AnimationPercent = 0.0f;
		Montage_Play(FindMontage/*, 1.0f*/);
		m_ChangeAnimationKey = Key;
		return;
	}

	if (m_AnimationPercent < m_MinAnimationPercent)
	{
		return;
	}

	// idle로 돌아오라고 해서 돌아오자마자 다시 어택 end가 다시 실행되서 다시 end
	if (false == Montage_IsPlaying(FindMontage))
	{
		m_MinAnimationPercent = _MinAnimationPercent;
		m_AnimationLen = FindMontage->GetPlayLength();
		m_AnimationTime = 0.0f;
		m_AnimationPercent = 0.0f;
		Montage_Play(FindMontage/*, 1.0f*/);
		m_ChangeAnimationKey = Key;
	}
}

UAnimMontage* UURAnimInstance::GetAnimation(int _Key)
{
	UAnimMontage** FindMontage = m_Animations.Find(_Key);

	if (nullptr == FindMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("animation Montage Null!"));
		return nullptr;
	}

	return *FindMontage;
}

void UURAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UURAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	m_AnimationTime += DeltaSeconds;
	if (0.0f < m_AnimationLen)
	{
		m_AnimationPercent = m_AnimationTime / m_AnimationLen;
	}
}
