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
	m_QuestProgress(QuestProgress::Default),
	m_IsRun(false),
	m_IsForwardDown(false),
	m_IsBackwardDown(false),
	m_IsLeftDown(false),
	m_IsRightDown(false),
	m_IsQSkillAttacking(false),
	m_IsESkillAttacking(false),
	m_IsRSkillAttacking(false),
	m_MouseXDPI(0.5f),
	m_MouseYDPI(0.5f),
	m_MoveSpeed(1.f),
	m_TeleportDist(600.f),
	m_IsQuesting(false),
	m_IsQuestCompletion(false)
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

	/*bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;*/


	/*GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 940.0f, 0.0f); 
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;*/
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;

	m_CameraSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(FName(TEXT("CameraSpringArm")));
	m_CameraSpringArmComponent->SetupAttachment(RootComponent);
	m_CameraSpringArmComponent->TargetArmLength = 800.0f;
	//m_CameraSpringArmComponent->SetRelativeRotation(FRotator(-55.0f, 0.0f, 0.0f));
	m_CameraSpringArmComponent->bDoCollisionTest = false;

	m_CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName(TEXT("CameraComponent")));
	m_CameraComponent->SetupAttachment(m_CameraSpringArmComponent);
	//m_CameraComponent->bUsePawnControlRotation = false;

	m_SkillQConsumedMP = 10.0;
	m_SkillEConsumedMP = 20.0;
	m_SkillRConsumedMP = 30.0;
}

void APlayCharacter::MouseMoveX(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}


	AddControllerYawInput(Value * m_MouseXDPI); 
}

void APlayCharacter::MouseMoveY(float Value)
{
	if (nullptr == m_CameraSpringArmComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("USpringArmComponent Cast Error!"));
		return;
	}

	// 사원수 복소수기반의 행렬을 만들어낼수있는 4개의 값들로 이루어진 수학적인 행렬인데.
	// 4x4크기의 회전행렬을 만들어 낼수 있다.

	if (Value == 0.0f)
	{
		return;
	}

	// UE_LOG(LogTemp, Error, TEXT("ControlRotation : %s"), *GetControlRotation().Euler().ToString());

	FRotator NextRot = GetControlRotation();
	NextRot.Add(Value * 2.0f, 0.0, 0.0f);
	FVector3d EulerRot = NextRot.Euler();

	if (EulerRot.Y > 50 && EulerRot.Y < 300)
	{
		// GetController()->SetControlRotation(NextRot);
		return;
	}

	//m_CameraSpringArmComponent->TargetArmLength -= Value * 10.0f;

	AddControllerPitchInput(-Value * m_MouseYDPI);
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

	AddMovementInput(-GetActorRightVector(), Value);

	m_IsLeftDown = true;

	if (GetAnimationInstance()->IsAnimMontage(DefaultAnimation::Forward)
		|| GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackWard)
		|| GetAnimationInstance()->IsAnimMontage(PlayerAnimationEx::Teleport))
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Left);

	AttackOff();
}

void APlayCharacter::PlayerRightMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	m_IsRightDown = true;

	AddMovementInput(GetActorRightVector(), Value);

	if (GetAnimationInstance()->IsAnimMontage(DefaultAnimation::Forward)
		|| GetAnimationInstance()->IsAnimMontage(DefaultAnimation::BackWard)
		|| GetAnimationInstance()->IsAnimMontage(PlayerAnimationEx::Teleport))
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Right);

	AttackOff();
}

void APlayCharacter::PlayerForwardMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	m_IsForwardDown = true;
	AddMovementInput(GetActorForwardVector(), Value);

	if (GetAnimationInstance()->IsAnimMontage(PlayerAnimationEx::Teleport))
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);

	AttackOff();
	
	
}

void APlayCharacter::PlayerBackwardMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	m_IsBackwardDown = true;
	AddMovementInput(-GetActorForwardVector(), Value);

	if (GetAnimationInstance()->IsAnimMontage(PlayerAnimationEx::Teleport))
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::BackWard);

	AttackOff();
}


void APlayCharacter::WheelKey(float Value)
{
	if (m_CameraSpringArmComponent->TargetArmLength + Value * 30.f < 2200.f &&
		m_CameraSpringArmComponent->TargetArmLength + Value * 30.f > 400.f)
	{
		m_CameraSpringArmComponent->TargetArmLength += Value * 30.f;
	}
	else if (m_CameraSpringArmComponent->TargetArmLength > 2200.f)
	{
		m_CameraSpringArmComponent->TargetArmLength = 2199.f;
	}
	else if(m_CameraSpringArmComponent->TargetArmLength < 400.f)
	{
		m_CameraSpringArmComponent->TargetArmLength = 401.f;
	}
}

void APlayCharacter::LeftAttack()
{
	if (true == IsAttack())
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
	AttackOn();
	
	
	
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

	if (m_IsQSkillAttacking)
	{
		return;
	}

	m_IsQSkillAttacking = true;

	AttackOn();
	GetAnimationInstance()->ChangeAnimMontage(PlayerAnimationEx::Skill1);

	m_MP -= m_SkillQConsumedMP;

	m_MPPercent = m_MP / m_PlayerInfo->MaxMP;
}

void APlayCharacter::SkillE()
{
	if (true == IsAttack())
	{
		return;
	}

	if (m_MP < m_SkillEConsumedMP)
	{
		return;
	}

	if (m_IsESkillAttacking)
	{
		return;
	}

	m_IsESkillAttacking = true;

	AttackOn();
	GetAnimationInstance()->ChangeAnimMontage(PlayerAnimationEx::Skill2);
	m_MP -= m_SkillEConsumedMP;

	m_MPPercent = m_MP / m_PlayerInfo->MaxMP;
}

void APlayCharacter::SkillR()
{
	if (true == IsAttack())
	{
		return;
	}

	AttackOn();
	GetAnimationInstance()->ChangeAnimMontage(PlayerAnimationEx::Skill3);
	m_MP -= m_SkillRConsumedMP;

	m_MPPercent = m_MP / m_PlayerInfo->MaxMP;
}

void APlayCharacter::ForwardKeyEnd()
{
	m_IsForwardDown = false;
	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
}

void APlayCharacter::BackwardKeyEnd()
{
	m_IsBackwardDown = false;
	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
}

void APlayCharacter::LeftKeyEnd()
{
	m_IsLeftDown = false;
	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
}

void APlayCharacter::RightKeyEnd()
{
	m_IsRightDown = false;
	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
}

void APlayCharacter::CtrlKeyDown()
{
	m_IsRun = true;
	GetCharacterMovement()->MaxWalkSpeed = 1000;
}

void APlayCharacter::CtrlKeyOn()
{
	m_IsRun = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void APlayCharacter::ShiftKeyDown()
{
	if (GetAnimationInstance()->IsAnimMontage(PlayerAnimationEx::Teleport))
	{
		return;
	}

	if (m_Stamina - 20.f < 0.f)
	{
		return;
	}

	// 텔레포트 어떤 방향으로 할지 판단하는 함수이다
	TeleportToJudge();

	m_Stamina -= 20.f;


	GetAnimationInstance()->ChangeAnimMontage(PlayerAnimationEx::Teleport);
}

void APlayCharacter::ShiftKeyOn()
{
}

void APlayCharacter::DamageOn(bool _IsKnockBack)
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

	SetDefaultData();
}

void APlayCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_IsForwardDown || m_IsBackwardDown || m_IsLeftDown || m_IsRightDown)
	{
		if (m_IsRun)
		{
			if (m_Stamina - DeltaTime * 15.f > 0.f)
			{
				m_Stamina -= DeltaTime * 15.f;
			}
			else if (m_Stamina < 0.f)
			{
				m_Stamina = 0.f;
			}

		}
	}
	if (!m_IsRun)
	{
		if (m_Stamina < m_PlayerInfo->MaxStamina)
		{
			m_Stamina += DeltaTime * 15.f;
		}
		else if (m_Stamina > m_PlayerInfo->MaxStamina)
		{
			m_Stamina = m_PlayerInfo->MaxStamina;
		}
	}

	if (m_IsRun)
	{
		if (m_Stamina <= 0.f)
		{
			m_IsRun = false;
			GetCharacterMovement()->MaxWalkSpeed = 600;
		}
	}

	CoolTimeTick(DeltaTime);
}

void APlayCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MouseMoveX"), this, &APlayCharacter::MouseMoveX);
	PlayerInputComponent->BindAxis(TEXT("MouseMoveY"), this, &APlayCharacter::MouseMoveY);

	PlayerInputComponent->BindAxis(FName(TEXT("LeftMove")), this, &APlayCharacter::PlayerLeftMove);
	PlayerInputComponent->BindAxis(FName(TEXT("RightMove")), this, &APlayCharacter::PlayerRightMove);
	PlayerInputComponent->BindAxis(FName(TEXT("ForwardMove")), this, &APlayCharacter::PlayerForwardMove);
	PlayerInputComponent->BindAxis(FName(TEXT("BackwardMove")), this, &APlayCharacter::PlayerBackwardMove);
	PlayerInputComponent->BindAction(FName(TEXT("ForwardMove")), EInputEvent::IE_Released, this, &APlayCharacter::ForwardKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("LeftMove")), EInputEvent::IE_Released, this, &APlayCharacter::LeftKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("RightMove")), EInputEvent::IE_Released, this, &APlayCharacter::RightKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("BackwardMove")), EInputEvent::IE_Released, this, &APlayCharacter::BackwardKeyEnd);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(FName(TEXT("AttackClick")), EInputEvent::IE_Pressed, this, &APlayCharacter::LeftAttack);
	PlayerInputComponent->BindAction(FName(TEXT("SkillQ")), EInputEvent::IE_Pressed, this, &APlayCharacter::SkillQ);
	PlayerInputComponent->BindAction(FName(TEXT("SkillE")), EInputEvent::IE_Pressed, this, &APlayCharacter::SkillE);
	PlayerInputComponent->BindAction(FName(TEXT("SkillR")), EInputEvent::IE_Pressed, this, &APlayCharacter::SkillR);

	PlayerInputComponent->BindAction(FName(TEXT("CtrlKey")), EInputEvent::IE_Pressed, this, &APlayCharacter::CtrlKeyDown);
	PlayerInputComponent->BindAction(FName(TEXT("CtrlKey")), EInputEvent::IE_Released, this, &APlayCharacter::CtrlKeyOn);

	PlayerInputComponent->BindAction(FName(TEXT("ShiftKey")), EInputEvent::IE_Pressed, this, &APlayCharacter::ShiftKeyDown);
	PlayerInputComponent->BindAction(FName(TEXT("ShiftKey")), EInputEvent::IE_Released, this, &APlayCharacter::ShiftKeyOn);

	

	PlayerInputComponent->BindAxis(FName(TEXT("WheelAxis")),this, &APlayCharacter::WheelKey);


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

void APlayCharacter::CallDamage(double _Damage, AActor* _Actor, bool _IsKnockBack, bool _IsCameraShake)
{
	Super::CallDamage(_Damage, _Actor, _IsKnockBack, _IsCameraShake);

	m_HPPercent = GetHP() / m_PlayerInfo->MaxHP;

	AUR_CircleActor* BossCIrcle = nullptr;

	if (_Actor != nullptr)
	{
		if (m_IsMoveing)
		{

		}
		else
		{
			GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::ForwardHit);
		}
	}
	else
	{
		GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::ForwardHit);

		FHitResult HitResult;
		m_PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(m_PlayerController, GetActorLocation());
	}
}

void APlayCharacter::SetDefaultData()
{
	// 스텟에 적용되는 내용들을 미리 적용한다.
	// m_PlayerInfo는 언리얼 데이터 주소를 갖고있는것.
	SetHP(m_PlayerInfo->HP);
	m_MaxHP = m_PlayerInfo->MaxHP;
	m_MaxHP = m_PlayerInfo->MaxMP;
	m_MPPercent = 1.0;
	m_HPPercent = 1.0;
	m_MP = m_PlayerInfo->MP;
	m_Stamina = m_PlayerInfo->MaxStamina;
	m_QSkillCurCollTime = 0.f;
	m_ESkillCurCollTime = 0.f;
	m_RSkillCurCollTime = 0.f;
	m_QSkillMaxCollTime = static_cast<int>(m_PlayerInfo->QSkillCollTime);
	m_ESkillMaxCollTime = static_cast<int>(m_PlayerInfo->ESkillCollTime);
	m_RSkillMaxCollTime = static_cast<int>(m_PlayerInfo->RSkillCollTime);
}

void APlayCharacter::TeleportToJudge()
{
	if (m_IsForwardDown && !m_IsBackwardDown && !m_IsLeftDown && !m_IsRightDown)
	{
		FVector Location = GetActorLocation() + GetActorForwardVector() * m_TeleportDist;
		SetActorLocation(Location);
	}

	else if (m_IsBackwardDown && !m_IsForwardDown && !m_IsLeftDown && !m_IsRightDown)
	{
		FVector Location = GetActorLocation() - GetActorForwardVector() * m_TeleportDist;
		SetActorLocation(Location);
	}

	else if (m_IsLeftDown && !m_IsForwardDown && !m_IsBackwardDown && !m_IsRightDown)
	{
		FVector Location = GetActorLocation() - GetActorRightVector() * m_TeleportDist;
		SetActorLocation(Location);
	}

	else if (m_IsRightDown && !m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
	{
		FVector Location = GetActorLocation() + GetActorRightVector() * m_TeleportDist;
		SetActorLocation(Location);
	}

	else if (m_IsForwardDown && m_IsLeftDown)
	{
		FVector Location = GetActorLocation() + (GetActorForwardVector() - GetActorRightVector()).GetSafeNormal() * m_TeleportDist;
		SetActorLocation(Location);
	}

	else if (m_IsForwardDown && m_IsRightDown)
	{
		FVector Location = GetActorLocation() + (GetActorForwardVector() + GetActorRightVector()).GetSafeNormal() * m_TeleportDist;
		SetActorLocation(Location);
	}

	else if (m_IsBackwardDown && m_IsLeftDown)
	{
		FVector Location = GetActorLocation() + (-GetActorForwardVector() - GetActorRightVector()).GetSafeNormal() * m_TeleportDist;
		SetActorLocation(Location);
	}

	else if (m_IsBackwardDown && m_IsRightDown)
	{
		FVector Location = GetActorLocation() + (-GetActorForwardVector() + GetActorRightVector()).GetSafeNormal() * m_TeleportDist;
		SetActorLocation(Location);
	}
}

void APlayCharacter::CoolTimeTick(float DeltaTime)
{
	if (m_IsQSkillAttacking)
	{
		m_QSkillCurCollTime += DeltaTime;

		if (m_QSkillCurCollTime >= m_QSkillMaxCollTime)
		{
			m_QSkillCurCollTime = 0.f;
			m_IsQSkillAttacking = false;
		}
	}
	else if (m_IsESkillAttacking)
	{
		m_ESkillCurCollTime += DeltaTime;

		if (m_ESkillCurCollTime >= m_ESkillMaxCollTime)
		{
			m_ESkillCurCollTime = 0.f;
			m_IsESkillAttacking = false;
		}
	}
	else if (m_IsRSkillAttacking)
	{
		m_RSkillCurCollTime += DeltaTime;

		if (m_RSkillCurCollTime >= m_RSkillMaxCollTime)
		{
			m_RSkillCurCollTime = 0.f;
			m_IsRSkillAttacking = false;
		}
	}
}

void APlayCharacter::Jump()
{
	Super::Jump();


}

void APlayCharacter::StopJumping()
{
	Super::StopJumping();


}
