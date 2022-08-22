// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "PlayerAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerCharacter::PlayerPickingMove()
{
}

void APlayerCharacter::PlayerLeftMove(float Value)
{
	if (Value == 0.f)
	{
		if (DirBit & static_cast<uint8>(PlayerAnimation::Left))
		{
			DirBit ^= static_cast<uint8>(PlayerAnimation::Left);
			AnimationInst->AnimationState = static_cast<PlayerAnimation>(DirBit);
		}
		return;
	}

	DirBit |= static_cast<uint8>(PlayerAnimation::Left);
	AnimationInst->AnimationState = static_cast<PlayerAnimation>(DirBit);
	// AddMovementInput
	// 블루프린트 플레이어에 들어가보면 무브먼트라고 동작에 관련된 물리등 다양한 것들이 종합되어 있는데
	// 해당 함수는 그것들을 이용해서 동작되게 만드는 함수이다.
	AddMovementInput(-GetActorRightVector(), Value);
}

void APlayerCharacter::PlayerRightMove(float Value)
{
	if (Value == 0.f)
	{
		if (DirBit & static_cast<uint8>(PlayerAnimation::Right))
		{
			DirBit ^= static_cast<uint8>(PlayerAnimation::Right);

			AnimationInst->AnimationState = static_cast<PlayerAnimation>(DirBit);
		}

		return;
	}

	DirBit |= static_cast<uint8>(PlayerAnimation::Right);

	AnimationInst->AnimationState = static_cast<PlayerAnimation>(DirBit);

	AddMovementInput(GetActorRightVector(), Value);
}

void APlayerCharacter::PlayerForwardMove(float Value)
{
	if (Value == 0.f)
	{
		if (DirBit & static_cast<uint8>(PlayerAnimation::Forward))
		{
			DirBit ^= static_cast<uint8>(PlayerAnimation::Forward);

			AnimationInst->AnimationState = static_cast<PlayerAnimation>(DirBit);
		}
		return;
	}

	DirBit |= static_cast<uint8>(PlayerAnimation::Forward);

	AnimationInst->AnimationState = static_cast<PlayerAnimation>(DirBit);

	AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerCharacter::PlayerBackwardMove(float Value)
{
	if (Value == 0.f)
	{
		if (DirBit & static_cast<uint8>(PlayerAnimation::Backward))
		{
			DirBit ^= static_cast<uint8>(PlayerAnimation::Backward);

			AnimationInst->AnimationState = static_cast<PlayerAnimation>(DirBit);
		}

		return;
	}


	DirBit |= static_cast<uint8>(PlayerAnimation::Backward);

	AnimationInst->AnimationState = static_cast<PlayerAnimation>(DirBit);

	AddMovementInput(-GetActorForwardVector(), Value);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimationInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	if (nullptr == AnimationInst &&
		AnimationInst->IsValidLowLevel())
	{
		// 없다면 에러 로그를 띄운다
		UE_LOG(LogTemp, Error, TEXT("Animation Instance Error!"));
	}
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("LeftMove"), this, &APlayerCharacter::PlayerLeftMove);
	PlayerInputComponent->BindAxis(TEXT("RightMove"), this, &APlayerCharacter::PlayerRightMove);
	PlayerInputComponent->BindAxis(TEXT("ForwardMove"), this, &APlayerCharacter::PlayerForwardMove);
	PlayerInputComponent->BindAxis(TEXT("BackwardMove"), this, &APlayerCharacter::PlayerBackwardMove);
}

