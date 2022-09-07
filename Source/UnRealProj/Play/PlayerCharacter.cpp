// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Animation/URAnimInstance.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// 프레임마다 Tick()을 호출하도록 이 문자를 설정합니다. 필요하지 않은 경우 이 기능을 해제하여 성능을 향상시킬 수 있습니다.
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

	// 범위기반 포문으로 갖고있는 애니메이션을 전부 넣어준다.
	for (auto& Anim : m_Animations)
	{
		AnimationInst->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}

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

