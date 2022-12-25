// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "UR_AttackEndAnimNotifyState.generated.h"

UENUM(BlueprintType)
enum class UPLAYER_TYPE : uint8
{
	Default UMETA(DisplayName = "선택x"),
	Wizard UMETA(DisplayName = "마법사"),
	Warrior UMETA(DisplayName = "전사")
};

UCLASS()
class UNREALPROJ_API UUR_AttackEndAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		UPLAYER_TYPE m_PlayerType;


protected:
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;


private:
	template <typename T, typename E>
	void ChnageAnimMontage(USkeletalMeshComponent* Comp, E Type)
	{
		T* Character = Comp->GetOwner<T>();

		if (!Character || !Character->IsValidLowLevel())
		{
			return;
		}

		Character->GetAnimationInstance()->ChangeAnimMontage(Type);
		Character->AttackOff();
	}
	
};
