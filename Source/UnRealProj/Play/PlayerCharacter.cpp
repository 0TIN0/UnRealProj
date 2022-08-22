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
	// �������Ʈ �÷��̾ ������ �����Ʈ��� ���ۿ� ���õ� ������ �پ��� �͵��� ���յǾ� �ִµ�
	// �ش� �Լ��� �װ͵��� �̿��ؼ� ���۵ǰ� ����� �Լ��̴�.
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
		// ���ٸ� ���� �α׸� ����
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

