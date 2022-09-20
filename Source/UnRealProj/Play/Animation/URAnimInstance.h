// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "URAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UURAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UURAnimInstance();

	void AddAnimMontage(int _Key, UAnimMontage* _Montage);

	template<typename EnumType>
	void ChangeAnimMontage(EnumType _Key, float _MinAnimationPercent = 0.f, bool Force = false)
	{
		ChangeAnimMontage(static_cast<int>(_Key), _MinAnimationPercent, Force);
	}

	void ChangeAnimMontage(int _Key, float _MinAnimationPercent = 0.f, bool Force = false);

	template<typename EnumType>
	FORCEINLINE bool IsAnimMontage(EnumType _Key)	const
	{
		return IsAnimMontage(static_cast<int>(_Key));
	}

	FORCEINLINE bool IsAnimMontage(int _Key) const
	{
		return m_ChangeAnimationKey == _Key;
	}
	template<typename EnumType>
	UAnimMontage* GetAnimation(EnumType _Key)
	{
		return GetAnimation(static_cast<int>(_Key));
	}

	UAnimMontage* GetAnimation(int _Key);

	UAnimMontage* GetCurrentMontage()
	{
		UAnimMontage** Anim = m_Animations.Find(m_ChangeAnimationKey);

		if (nullptr == Anim)
		{
			return nullptr;
		}

		return *Anim;
	}


private:
	// 언리얼의 맵은 해쉬
	// 언리얼은 좀 빠른 맵이고
	UPROPERTY(Category = "AnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, UAnimMontage*> m_Animations;

	int m_ChangeAnimationKey;

	float m_AnimationTime;
	float m_AnimationLen;
	float m_AnimationPercent;
	float m_MinAnimationPercent;

protected:
	// 이녀석이 만들어질때 이니셜라이즈 할 문제가 있다면 이녀석으로
	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
