// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayCharacter.h"

APlayCharacter::APlayCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayCharacter::PlayerPickingMove()
{
}

void APlayCharacter::PlayerLeftMove(float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Left);
	AddMovementInput(-GetActorRightVector(), Value);
}

void APlayCharacter::PlayerRightMove(float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Right);
	AddMovementInput(GetActorRightVector(), Value);
}

void APlayCharacter::PlayerForwardMove(float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);
	AddMovementInput(GetActorForwardVector(), Value);
}

void APlayCharacter::PlayerBackwardMove(float Value)
{
	if (Value == 0.f)
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::BackWard);
	AddMovementInput(-GetActorForwardVector(), Value);
}

void APlayCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (0 == m_DirBit && false == IsAttack())
	{
		GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
	}

	m_DirBit = 0;
}

void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis(FName(TEXT("LeftMove")), this, &APlayCharacter::PlayerLeftMove);
	PlayerInputComponent->BindAxis(FName(TEXT("RightMove")), this, &APlayCharacter::PlayerRightMove);
	PlayerInputComponent->BindAxis(FName(TEXT("ForwardMove")), this, &APlayCharacter::PlayerForwardMove);
	PlayerInputComponent->BindAxis(FName(TEXT("BackwardMove")), this, &APlayCharacter::PlayerBackwardMove);
}
