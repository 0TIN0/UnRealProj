// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlaySound.h"
#include "Global/UREnum.h"
#include "UR_HitSoundNotify.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UUR_HitSoundNotify : public UAnimNotify_PlaySound
{
	GENERATED_BODY()

public:
	UUR_HitSoundNotify();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		class USoundBase* m_WarriorHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		class USoundBase* m_PirateHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		class USoundBase* m_SparrowHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		class USoundBase* m_KhaimeraHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		UPLAYER_TYPE m_PlayerType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		UMONSTER_TYPE m_MonsterType;


protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
