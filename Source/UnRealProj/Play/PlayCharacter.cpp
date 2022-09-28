// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

APlayCharacter::APlayCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Tags.Add("Player");

	UCapsuleComponent* Component = FindComponentByClass<UCapsuleComponent>();

	if (Component)
	{
		Component->SetCollisionProfileName(FName(TEXT("Player")));
	}
}

void APlayCharacter::PlayerPickingMove()
{
}

void APlayCharacter::PlayerLeftMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Left);
	AddMovementInput(-GetActorRightVector(), Value);
}

void APlayCharacter::PlayerRightMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Right);
	AddMovementInput(GetActorRightVector(), Value);
}

void APlayCharacter::PlayerForwardMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);
	AddMovementInput(GetActorForwardVector(), Value);
}

void APlayCharacter::PlayerBackwardMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::BackWard);
	AddMovementInput(-GetActorForwardVector(), Value);
}

void APlayCharacter::LeftAttack()
{
	if (true == IsAttack())
	{
		return;
	}

	AttackOn();
	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
}

void APlayCharacter::SkillQ()
{
	if (true == IsAttack())
	{
		return;
	}

	AttackOn();
	GetAnimationInstance()->ChangeAnimMontage(PlayerAnimationEx::Skill1);
}

void APlayCharacter::MoveKeyEnd()
{
	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
}

void APlayCharacter::DamageOn()
{
	TArray<UActorComponent*> Array = GetDamageCollision();

	for (size_t i = 0; i < Array.Num(); ++i)
	{
		bool Check = false;

		USphereComponent* Sphere = Cast<USphereComponent>(Array[i]);

		if (!Sphere)
			return;

		TArray<FHitResult> Targets = CollisionCheck(Sphere->GetComponentLocation(),
			FName(TEXT("PlayerAttackTrace")), Sphere->GetCollisionShape());

		for (int MonsterCount = 0; MonsterCount < Targets.Num(); ++MonsterCount)
		{
			AURCharacter* Character = Cast<AURCharacter>(Targets[MonsterCount].GetActor());

			if (Character)
			{
				Check = true;
				Character->CallDamage(1.0);
			}
		}

		FColor Color = FColor::Green;

		if (Check)
		{
			Color = FColor::Red;
		}

		DrawDebugSphere(GetWorld(), Sphere->GetComponentLocation(), Sphere->GetScaledSphereRadius(),
			15, Color, false, 0.1f);
	}
}

void APlayCharacter::BeginPlay()
{
	Super::BeginPlay();


	for (auto& Anim : m_PlayerAnimations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}
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
	PlayerInputComponent->BindAction(FName(TEXT("AttackClick")), EInputEvent::IE_Pressed, this, &APlayCharacter::LeftAttack);
	PlayerInputComponent->BindAction(FName(TEXT("SkillQ")), EInputEvent::IE_Pressed, this, &APlayCharacter::SkillQ);
}

void APlayCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
}

void APlayCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
}

void APlayCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
}
