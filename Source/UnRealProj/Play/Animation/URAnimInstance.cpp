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

void UURAnimInstance::ChangeAnimMontage(int Key)
{
	m_ChangeAnimationKey = Key;

	UAnimMontage** Anim = m_Animations.Find(m_ChangeAnimationKey);

	if (!Anim)
	{
		UE_LOG(LogTemp, Error, TEXT("animation Montage Null!"));
		return;
	}

	if (!Montage_IsPlaying(*Anim))
		Montage_Play(*Anim);
}

void UURAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
}

void UURAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}
