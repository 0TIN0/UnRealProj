// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Math/Rotator.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BluePrintType)
enum class PlayerAnimation : uint8
{
	Idle UMETA(DisplayName = "서있는 모션"),
	Left UMETA(DisplayName = "왼쪽"),
	Right UMETA(DisplayName = "오른쪽"),
	Forward = 4 UMETA(DisplayName = "앞"),
	Backward = 8 UMETA(DisplayName = "뒤"),
	LeftForward = 5 UMETA(DisplayName = "왼쪽앞"),
	RightForward = 6 UMETA(DisplayName = "오른쪽앞"),
	LeftBackward = 9 UMETA(DisplayName = "왼쪽뒤"),
	RightBackward = 10 UMETA(DisplayName = "오른쪽뒤")
};

UCLASS()
class UNREALPROJ_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserContents")
	PlayerAnimation AnimationState;

	class UPlayerAnimInstance* AnimationInst;
	uint32 DirBit;


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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
