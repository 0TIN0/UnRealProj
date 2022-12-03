// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Global/URGameInstance.h"
#include "Global/URStructs.h"
#include "Camera/PlayerCameraManager.h"
#include "Skill/UR_LightningActor.h"
#include "Skill/Boss/UR_CircleActor.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APlayCharacter::APlayCharacter()	:
	m_HPPercent(1.0)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	Tags.Add("Player");

	UCapsuleComponent* Component = FindComponentByClass<UCapsuleComponent>();

	if (Component)
	{
		Component->SetCollisionProfileName(FName(TEXT("Player")));
	}

	RootComponent = Component;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;


	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 940.0f, 0.0f); 
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	m_CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("CameraSpringArm")));
	m_CameraSpringArmComponent->SetupAttachment(RootComponent);
	m_CameraSpringArmComponent->SetUsingAbsoluteRotation(true);
	m_CameraSpringArmComponent->TargetArmLength = 1200.0f;
	m_CameraSpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 45.0f, 0.0f));
	m_CameraSpringArmComponent->bDoCollisionTest = false;

	m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("CameraComponent")));
	m_CameraComponent->SetupAttachment(m_CameraSpringArmComponent);
	m_CameraComponent->bUsePawnControlRotation = false;

	m_ElevatorArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("ElevatorSpringArm")));
	m_ElevatorArmComponent->SetupAttachment(RootComponent);
	m_ElevatorArmComponent->TargetArmLength = 0.0f;
	m_ElevatorArmComponent->SetRelativeLocation(FVector(0.0, 0.0, 300.0f));
	m_ElevatorArmComponent->bDoCollisionTest = false;

	m_ElevatorCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ElevatorCamera"));
	m_ElevatorCamera->SetupAttachment(m_ElevatorArmComponent);
	m_ElevatorCamera->bUsePawnControlRotation = false;

	m_SkillQConsumedMP = 10.0;
	m_SkillWConsumedMP = 20.0;
}

void APlayCharacter::PlayerPickingMove()
{
}

//void APlayCharacter::PlayerLeftMove(float Value)
//{
//	if (Value == 0.f || true == IsAttack())
//	{
//		return;
//	}
//
//	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Left);
//	AddMovementInput(-GetActorRightVector(), Value);
//}
//
//void APlayCharacter::PlayerRightMove(float Value)
//{
//	if (Value == 0.f || true == IsAttack())
//	{
//		return;
//	}
//
//	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Right);
//	AddMovementInput(GetActorRightVector(), Value);
//}
//
//void APlayCharacter::PlayerForwardMove(float Value)
//{
//	if (Value == 0.f || true == IsAttack())
//	{
//		return;
//	}
//
//	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);
//	AddMovementInput(GetActorForwardVector(), Value);
//}
//
//void APlayCharacter::PlayerBackwardMove(float Value)
//{
//	if (Value == 0.f || true == IsAttack())
//	{
//		return;
//	}
//
//	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::BackWard);
//	AddMovementInput(-GetActorForwardVector(), Value);
//}

void APlayCharacter::LeftAttack()
{
	if (true == IsAttack() && !m_IsSkillW)
	{
		return;
	}

	FHitResult HitResult;
	m_PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	FVector PlayerLocation = GetActorLocation();

	if (!m_IsSkillW)
	{
		// 마웃 커서의 위치가 땅 바닥이여서 플레이어 배꼽위치로 맞춰줌
		HitResult.ImpactPoint.Z = PlayerLocation.Z;
		// 플레이어 위치랑 마우스 위치를 넣어주어서 타겟 로테이터를 얻어서 플레이어 로테이션을 바꿈
		FRotator TargetRotator = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, HitResult.ImpactPoint);
		SetActorRotation(TargetRotator);
		GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
	}
	
	else
	{
		FTransform SpawnTransform = FTransform(HitResult.ImpactPoint);
		AActor* NewActor = GetWorld()->SpawnActor<AActor>(m_SpawnActorClass, SpawnTransform);

		//AUR_LightningActor* Lightning = Cast<AUR_LightningActor>(NewActor);
	}

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(m_PlayerController, GetActorLocation());
}

void APlayCharacter::SkillQ()
{
	if (true == IsAttack())
	{
		return;
	}

	if (m_MP < m_SkillQConsumedMP)
	{
		return;
	}
	FHitResult HitResult;
	m_PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(m_PlayerController, GetActorLocation());
	FVector PlayerLocation = GetActorLocation();

	// 마웃 커서의 위치가 땅 바닥이여서 플레이어 배꼽위치로 맞춰줌
	HitResult.ImpactPoint.Z = PlayerLocation.Z;
	// 플레이어 위치랑 마우스 위치를 넣어주어서 타겟 로테이터를 얻어서 플레이어 로테이션을 바꿈
	FRotator TargetRotator = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, HitResult.ImpactPoint);
	SetActorRotation(TargetRotator);
	AttackOn();
	GetAnimationInstance()->ChangeAnimMontage(PlayerAnimationEx::Skill1);

	m_MP -= m_SkillQConsumedMP;

	m_MPPercent = m_MP / m_PlayerInfo->MaxMP;
}

void APlayCharacter::SkillW()
{
	if (true == IsAttack())
	{
		return;
	}

	if (m_MP < m_SkillWConsumedMP)
	{
		return;
	}

	AttackOn();
	GetAnimationInstance()->ChangeAnimMontage(PlayerAnimationEx::Skill2);

	m_IsSkillW = true;
	m_MP -= m_SkillWConsumedMP;

	m_MPPercent = m_MP / m_PlayerInfo->MaxMP;
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

void APlayCharacter::ReSetHPPercent()
{
	m_HPPercent = GetHP() / m_PlayerInfo->MaxHP;
}

double APlayCharacter::GetMaxHP()
{
	return m_PlayerInfo->MaxHP;
}

void APlayCharacter::BeginPlay()
{
	Super::BeginPlay();

	m_PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!m_PlayerController || !m_PlayerController->IsValidLowLevel())
	{
		return;
	}

	for (auto& Anim : m_PlayerAnimations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}


	m_PlayerInfo = GetWorld()->GetGameInstance<UURGameInstance>()->GetPlayerData(FName(TEXT("Player")));

	SetHP(m_PlayerInfo->HP);
	m_MPPercent = 1.0;
	m_MP = m_PlayerInfo->MP;
}

void APlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if(GetMovementComponent())*/
}

void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/*PlayerInputComponent->BindAxis(FName(TEXT("LeftMove")), this, &APlayCharacter::PlayerLeftMove);
	PlayerInputComponent->BindAxis(FName(TEXT("RightMove")), this, &APlayCharacter::PlayerRightMove);
	PlayerInputComponent->BindAxis(FName(TEXT("ForwardMove")), this, &APlayCharacter::PlayerForwardMove);
	PlayerInputComponent->BindAxis(FName(TEXT("BackwardMove")), this, &APlayCharacter::PlayerBackwardMove);*/
	PlayerInputComponent->BindAction(FName(TEXT("LeftMove")), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("RightMove")), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("ForwardMove")), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("BackwardMove")), EInputEvent::IE_Released, this, &APlayCharacter::MoveKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("AttackClick")), EInputEvent::IE_Pressed, this, &APlayCharacter::LeftAttack);
	PlayerInputComponent->BindAction(FName(TEXT("SkillQ")), EInputEvent::IE_Pressed, this, &APlayCharacter::SkillQ);
	PlayerInputComponent->BindAction(FName(TEXT("SkillW")), EInputEvent::IE_Pressed, this, &APlayCharacter::SkillW);
}

void APlayCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
}

void APlayCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
}

void APlayCharacter::NotifyActorEndOverlap(AActor* OtherActor)
{
	/*APlayerController* OurPlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (OurPlayerController)
	{
		OurPlayerController->Possess(Cast<APawn>(m_CameraComponent));
	}*/
}

void APlayCharacter::CallDamage(double _Damage, AActor* _Actor)
{
	Super::CallDamage(_Damage);

	m_HPPercent = GetHP() / m_PlayerInfo->MaxHP;

	AUR_CircleActor* BossCIrcle = nullptr;

	if (_Actor != nullptr)
	{
		if (m_IsMoveing)
		{

		}
		else
		{
			GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Hit);
		}
	}
	else
	{
		GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Hit);

		FHitResult HitResult;
		m_PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(m_PlayerController, GetActorLocation());
	}
}
