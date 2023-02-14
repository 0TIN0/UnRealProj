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

void UURAnimInstance::SetDefaultMontage(int _Key)
{
	m_DefaultKey = _Key;
}

void UURAnimInstance::ChangeAnimMontage(int _Key, bool _Force)
{
	UAnimMontage* FindMontage = GetAnimation(_Key);

	// 애님 몽타주의 총 길이
	float Len = FindMontage->GetPlayLength();

	if (!Montage_IsPlaying(FindMontage) || _Force)
	{
		m_Time = 0.f;
		Montage_Play(FindMontage);
		m_CurrentAnimationKey = _Key;
	}
}

bool UURAnimInstance::IsAnimMontage(int _Key) const
{
	return m_CurrentAnimationKey == _Key;
}

UAnimMontage* UURAnimInstance::GetAnimation(int _Key)
{
	// 처음 업데이트가 엑터 비긴보다 먼저 돌아가서 비어있을경우 리턴 널 해준다.
	if (m_Animations.IsEmpty())
	{
		return nullptr;
	}

	UAnimMontage** FindMontage = m_Animations.Find(_Key);

	if (nullptr == FindMontage)
	{
		UE_LOG(LogTemp, Error, TEXT("animation Montage Null!"));
		return nullptr;
	}

	return *FindMontage;
}

int UURAnimInstance::FindMontageKey(UAnimMontage* _Montage)
{
	for (auto& Elem : m_Animations)
	{
		if (Elem.Value == _Montage)
		{
			return Elem.Key;
		}
	}

	return 0;
}

void UURAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UURAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UAnimMontage* FindMontage = GetAnimation(m_CurrentAnimationKey);

	if (!FindMontage)
	{
		return;
	}

	float Len = FindMontage->GetPlayLength();
	
	m_Time += DeltaSeconds * FindMontage->RateScale;

	float Percent = m_Time / Len;

	if (1.f <= Percent)
	{
		//m_CurrentAnimationKey = m_DefaultKey;
		ChangeAnimMontage(m_CurrentAnimationKey, true);
	}
}
