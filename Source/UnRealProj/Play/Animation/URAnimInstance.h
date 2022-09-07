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
	// �𸮾��� ���� �ؽ�
	// �𸮾��� �� ���� ���̰�
	UPROPERTY(Category = "AnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, UAnimMontage*> m_Animations;

	int m_ChangeAnimationKey;

protected:
	// �̳༮�� ��������� �̴ϼȶ����� �� ������ �ִٸ� �̳༮����
	void NativeBeginPlay() override;

	void NativeUpdateAnimation(float DeltaSeconds) override;
	
};
