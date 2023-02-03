// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Global/UREnum.h"
#include "UR_CreateObjAnimNotifyState.generated.h"


UENUM(BlueprintType)
enum class ActorType : uint8
{
	// 1100 
	Normal UMETA(DisplayName = "노멀"),
	Projectile UMETA(DisplayName = "발사체")
};

UCLASS()
class UNREALPROJ_API UUR_CreateObjAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AActor>	m_SpawnActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
		UMONSTER_TYPE m_MonsterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	FName m_SocketName;

	// 프로젝타일이 어떤거냐에따라 z값의 위치가 다르기 때문 z값을 Add할 수 있는 변수를 만듬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	float m_AddLocationZ;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	FName m_CollisionProfileName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	float m_Speed;;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	float m_LifeTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents", meta = (AllowPrivateAccess = "true"))
	ActorType m_ActorType;


	TArray<std::pair<AActor*, FTransform>> m_ArrowArray;

protected:
	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;


private:
	void CreateSparrowSP4Shoot(USkeletalMeshComponent* _MeshComp, class AUR_SparrowSubBoss* _Boss);
	void CreateSparrowSP5Shoot(USkeletalMeshComponent* _MeshComp, class AUR_SparrowSubBoss* _Boss);
	void CreateSparrowBurstShoot(USkeletalMeshComponent* _MeshComp, class AUR_SparrowSubBoss* _Boss);
};
