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
	void ChangeAnimMontage(EnumType _Key)
	{
		ChangeAnimMontage(static_cast<int>(_Key));
	}

	void ChangeAnimMontage(int _Key);

private:
	// 언리얼의 맵은 해쉬
	// 언리얼은 좀 빠른 맵이고
	UPROPERTY(Category = "AnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, UAnimMontage*> m_Animations;

	int m_ChangeAnimationKey;

protected:
	// 이녀석이 만들어질때 이니셜라이즈 할 문제가 있다면 이녀석으로
	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
