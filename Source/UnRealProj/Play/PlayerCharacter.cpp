// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Animation/URAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// �����Ӹ��� Tick()�� ȣ���ϵ��� �� ���ڸ� �����մϴ�. �ʿ����� ���� ��� �� ����� �����Ͽ� ������ ����ų �� �ֽ��ϴ�.
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
		}
		return;
	}

	DirBit |= static_cast<uint8>(PlayerAnimation::Left);
	AnimationInst->ChangeAnimMontage(PlayerAnimation::Left);
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
		}

		return;
	}

	DirBit |= static_cast<uint8>(PlayerAnimation::Right);

	AnimationInst->ChangeAnimMontage(PlayerAnimation::Right);

	AddMovementInput(GetActorRightVector(), Value);
}

void APlayerCharacter::PlayerForwardMove(float Value)
{
	if (Value == 0.f)
	{
		if (DirBit & static_cast<uint8>(PlayerAnimation::Forward))
		{
			DirBit ^= static_cast<uint8>(PlayerAnimation::Forward);
		}
		return;
	}

	DirBit |= static_cast<uint8>(PlayerAnimation::Forward);

	AnimationInst->ChangeAnimMontage(PlayerAnimation::Forward);

	AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerCharacter::PlayerBackwardMove(float Value)
{
	if (Value == 0.f)
	{
		if (DirBit & static_cast<uint8>(PlayerAnimation::Backward))
		{
			DirBit ^= static_cast<uint8>(PlayerAnimation::Backward);
		}

		return;
	}


	DirBit |= static_cast<uint8>(PlayerAnimation::Backward);

	AnimationInst->ChangeAnimMontage(PlayerAnimation::Backward);

	AddMovementInput(-GetActorForwardVector(), Value);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AnimationInst = Cast<UURAnimInstance>(GetMesh()->GetAnimInstance());

	// ������� �������� �����ִ� �ִϸ��̼��� ���� �־��ش�.
	for (auto& Anim : m_Animations)
	{
		AnimationInst->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}

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

	if (0 == DirBit)
	{
		if (AnimationInst)
			AnimationInst->ChangeAnimMontage(PlayerAnimation::Idle);
	}

	DirBit = 0;
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

