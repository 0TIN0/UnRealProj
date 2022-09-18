// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayCharacter.h"

APlayCharacter::APlayCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Player");
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

void APlayCharacter::MoveKeyEnd()
{
	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
}

void APlayCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName(TEXT("LeftMove")), this, &APlayCharacter::PlayerLeftMove);
	PlayerInputComponent->BindAxis(FName(TEXT("RightMove")), this, &APlayCharacter::PlayerRightMove);
	PlayerInputComponent->BindAxis(FName(TEXT("ForwardMove")), this, &APlayCharacter::PlayerForwardMove);
	PlayerInputComponent->BindAxis(FName(TEXT("BackwardMove")), this, &APlayCharacter::PlayerBackwardMove);
	PlayerInputComponent->BindAction(FName(TEXT("LeftMove")), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("RightMove")), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("ForwardMove")), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("BackwardMove")), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
}
