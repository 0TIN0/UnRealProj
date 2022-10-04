// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "URCharacter.h"
#include "PlayCharacter.generated.h"

UENUM(BlueprintType)
enum class PlayerAnimationEx : uint8
{
	// 1100 
	Min UMETA(DisplayName = "Don't touch"),
	Skill1 = static_cast<int>(DefaultAnimation::Max) UMETA(DisplayName = "Skill1"),
	Skill2 UMETA(DisplayName = "Skill2"),
	Skill3 UMETA(DisplayName = "Skill3"),
};

UCLASS()
class UNREALPROJ_API APlayCharacter : public AURCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(Category = "PlayerAnimationData", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<PlayerAnimationEx, UAnimMontage*> m_PlayerAnimations;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* m_CameraComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* m_CameraSpringArmComponent;

public:
	APlayCharacter();

	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerPickingMove();
	
	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerLeftMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerRightMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerForwardMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
	void PlayerBackwardMove(float Value);

	UFUNCTION(BlueprintCallable, Category = UR)
	void LeftAttack();

	UFUNCTION(BlueprintCallable, Category = UR)
	void SkillQ();

	UFUNCTION(BlueprintCallable, Category = UR)
	void MoveKeyEnd();

	void DamageOn() override;


protected:
	void BeginPlay() override;

	void Tick(float DeltaTime)	override;

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void NotifyActorEndOverlap(AActor* OtherActor) override;

};
