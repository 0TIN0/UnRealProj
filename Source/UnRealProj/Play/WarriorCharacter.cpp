// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/WarriorCharacter.h"
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
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AWarriorCharacter::AWarriorCharacter() :
	m_QuestProgress(QuestProgress::Default),
	m_IsRun(false),
	m_IsForwardDown(false),
	m_IsBackwardDown(false),
	m_IsLeftDown(false),
	m_IsRightDown(false),
	m_IsQSkillAttacking(false),
	m_IsESkillAttacking(false),
	m_IsRSkillAttacking(false),
	m_IsComboAttack(false),
	m_IsCombating(false),
	m_CombatTime(7.f),
	m_MouseXDPI(0.5f),
	m_MouseYDPI(0.5f),
	m_MoveSpeed(1.f),
	m_DashDist(600.f),
	m_IsQuesting(false),
	m_IsQuestCompletion(false)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/Resource/Play/Curve/UR_DashCurve.UR_DashCurve'"));
	check(Curve.Succeeded());

	FloatCurve = Curve.Object;

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

void AWarriorCharacter::MouseMoveX(float Value)
{
	if (Value == 0.0f)
	{
		return;
	}


	AddControllerYawInput(Value * m_MouseXDPI);
}

void AWarriorCharacter::MouseMoveY(float Value)
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

void AWarriorCharacter::PlayerPickingMove()
{
}

void AWarriorCharacter::PlayerLeftMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	AddMovementInput(-GetActorRightVector(), Value);

	m_IsLeftDown = true;

	if (JudgeFunc())
	{
		return;
	}

	if (!m_IsCombating)
	{
		if (!m_IsRun)
		{
			if (m_IsLeftDown && !m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Left);
			}
			else if (m_IsLeftDown && m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::ForWardLeft);
			}
			else if (m_IsLeftDown && m_IsBackwardDown && !m_IsRightDown && !m_IsForwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::BackWardLeft);
			}
		}
		else
		{
			if (m_IsLeftDown && !m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::RunLeft);
			}
			else if (m_IsLeftDown && m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::RunForwardLeft);
			}
			else if (m_IsLeftDown && m_IsBackwardDown && !m_IsRightDown && !m_IsForwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::RunBackwardLeft);
			}
		}
	}
	else
	{
		if (!m_IsRun)
		{
			if (m_IsLeftDown && !m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatWalkLeft);
			}
			else if (m_IsLeftDown && m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatWalkForWardLeft);
			}
			else if (m_IsLeftDown && m_IsBackwardDown && !m_IsRightDown && !m_IsForwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatWalkBackWardLeft);
			}
		}
		else
		{
			if (m_IsLeftDown && !m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatRunLeft);
			}
			else if (m_IsLeftDown && m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatRunForWardLeft);
			}
			else if (m_IsLeftDown && m_IsBackwardDown && !m_IsRightDown && !m_IsForwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatRunBackWardLeft);
			}
		}
	}

	AttackOff();
}

void AWarriorCharacter::PlayerRightMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}


	AddMovementInput(GetActorRightVector(), Value);
	m_IsRightDown = true;

	if (JudgeFunc())
	{
		return;
	}

	if (!m_IsCombating)
	{
		if (!m_IsRun)
		{
			if (m_IsRightDown && !m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Right);
			}
			else if (m_IsRightDown && m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::ForWardRight);
			}
			else if (m_IsRightDown && m_IsBackwardDown && !m_IsLeftDown && !m_IsForwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::BackWardRight);
			}
		}
		else
		{
			if (m_IsRightDown && !m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::RunRight);
			}
			else if (m_IsRightDown && m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::RunForwardRight);
			}
			else if (m_IsRightDown && m_IsBackwardDown && !m_IsLeftDown && !m_IsForwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::RunBackwardRight);
			}
		}
	}
	else
	{
		if (!m_IsRun)
		{
			if (m_IsRightDown && !m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatWalkRight);
			}
			else if (m_IsRightDown && m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatWalkForWardRight);
			}
			else if (m_IsRightDown && m_IsBackwardDown && !m_IsLeftDown && !m_IsForwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatWalkBackWardRight);
			}
		}
		else
		{
			if (m_IsRightDown && !m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatRunRight);
			}
			else if (m_IsRightDown && m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatRunForWardRight);
			}
			else if (m_IsRightDown && m_IsBackwardDown && !m_IsLeftDown && !m_IsForwardDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatRunBackWardRight);
			}
		}
	}

	AttackOff();
}

void AWarriorCharacter::PlayerForwardMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	m_IsForwardDown = true;
	AddMovementInput(GetActorForwardVector(), Value);

	if (JudgeFunc())
	{
		return;
	}


	if (!m_IsCombating)
	{
		if (!m_IsRun)
		{
			if (m_IsForwardDown && !m_IsLeftDown && !m_IsRightDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Forward);
			}
		}
		else
		{
			if (m_IsForwardDown && !m_IsLeftDown && !m_IsRightDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::RunForward);
			}
		}
	}
	else
	{
		if (!m_IsRun)
		{
			if (m_IsForwardDown && !m_IsLeftDown && !m_IsRightDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatWalkForward);
			}
		}
		else
		{
			if (m_IsForwardDown && !m_IsLeftDown && !m_IsRightDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatRunForward);
			}
		}
	}

	AttackOff();


}

void AWarriorCharacter::PlayerBackwardMove(float Value)
{
	if (Value == 0.f || true == IsAttack())
	{
		return;
	}

	m_IsBackwardDown = true;
	AddMovementInput(-GetActorForwardVector(), Value);

	if (JudgeFunc())
	{
		return;
	}


	if (!m_IsCombating)
	{
		if (!m_IsRun)
		{
			if (m_IsBackwardDown && !m_IsLeftDown && !m_IsRightDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::BackWard);
			}
		}
		else
		{
			if (m_IsBackwardDown && !m_IsLeftDown && !m_IsRightDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::RunBackward);
			}
		}
	}
	else
	{
		if (!m_IsRun)
		{
			if (m_IsBackwardDown && !m_IsLeftDown && !m_IsRightDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatWalkBackWard);
			}
		}
		else
		{
			if (m_IsBackwardDown && !m_IsLeftDown && !m_IsRightDown)
			{
				GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatRunBackWard);
			}
		}
	}

	AttackOff();
}


void AWarriorCharacter::WheelKey(float Value)
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
	else if (m_CameraSpringArmComponent->TargetArmLength < 400.f)
	{
		m_CameraSpringArmComponent->TargetArmLength = 401.f;
	}
}

void AWarriorCharacter::LeftAttack()
{
	m_IsComboAttack = true;
	m_IsCombating = true;

	if (true == IsAttack())
	{
		return;
	}

	GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Attack);
	AttackOn();



}

void AWarriorCharacter::LeftAttackUp()
{
	m_IsComboAttack = false;
}

void AWarriorCharacter::SkillQ()
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
	GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::Skill1);

	m_MP -= m_SkillQConsumedMP;

	m_MPPercent = m_MP / m_PlayerInfo->MaxMP;
}

void AWarriorCharacter::SkillE()
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
	GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::Skill2);
	m_MP -= m_SkillEConsumedMP;

	m_MPPercent = m_MP / m_PlayerInfo->MaxMP;
}

void AWarriorCharacter::SkillR()
{
	if (true == IsAttack())
	{
		return;
	}

	AttackOn();
	GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::Skill3);
	m_MP -= m_SkillRConsumedMP;

	m_MPPercent = m_MP / m_PlayerInfo->MaxMP;
}

void AWarriorCharacter::ForwardKeyEnd()
{
	m_IsForwardDown = false;

	if (JudgeFunc())
	{
		return;
	}
	
	if (!m_IsCombating)
	{
		GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
	}
	else
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatIdle);
	}
}

void AWarriorCharacter::BackwardKeyEnd()
{
	m_IsBackwardDown = false;

	if (JudgeFunc())
	{
		return;
	}

	if (!m_IsCombating)
	{
		GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
	}
	else
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatIdle);
	}
}

void AWarriorCharacter::LeftKeyEnd()
{
	m_IsLeftDown = false;

	if (JudgeFunc())
	{
		return;
	}

	if (!m_IsCombating)
	{
		GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
	}
	else
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatIdle);
	}
}

void AWarriorCharacter::RightKeyEnd()
{
	m_IsRightDown = false;

	if (JudgeFunc())
	{
		return;
	}

	if (!m_IsCombating)
	{
		GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
	}
	else
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorCombatAnimation::CombatIdle);
	}
}

void AWarriorCharacter::CtrlKeyDown()
{
	m_IsRun = true;
	GetCharacterMovement()->MaxWalkSpeed = 1000;
}

void AWarriorCharacter::CtrlKeyOn()
{
	m_IsRun = false;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AWarriorCharacter::ShiftKeyDown()
{
	if (DashJudgeFunc())
	{
		return;
	}

	if (m_Stamina - 20.f < 0.f)
	{
		return;
	}

	// 텔레포트 어떤 방향으로 할지 판단하는 함수이다
	DashToJudge();
	AttackOff();

	m_Stamina -= 20.f;

	if (m_IsRightDown && !m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::DashRight);
	}
	else if (m_IsLeftDown && !m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::DashLeft);
	}
	else if (m_IsForwardDown && !m_IsLeftDown && !m_IsRightDown && !m_IsBackwardDown)
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::DashForward);
	}
	else if (m_IsBackwardDown && !m_IsForwardDown && !m_IsRightDown && !m_IsLeftDown)
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::DashBackward);
	}
	else if (m_IsRightDown && m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::DashForwardRight);
	}
	else if (m_IsLeftDown && m_IsForwardDown && !m_IsRightDown && !m_IsBackwardDown)
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::DashForwardLeft);
	}
	else if (m_IsRightDown && m_IsBackwardDown && !m_IsLeftDown && !m_IsForwardDown)
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::DashBackwardRight);
	}
	else if (m_IsLeftDown && m_IsBackwardDown && !m_IsRightDown && !m_IsForwardDown)
	{
		GetAnimationInstance()->ChangeAnimMontage(WarriorAnimation::DashBackwardLeft);
	}
}

void AWarriorCharacter::ShiftKeyOn()
{
}

void AWarriorCharacter::DamageOn()
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
void AWarriorCharacter::BeginPlay()
{
	FOnTimelineFloat onTimelineCallback;
	FOnTimelineEventStatic onTimelineFinishedCallback;

	Super::BeginPlay();

	if (FloatCurve != NULL)
	{
		MyTimeline = NewObject<UTimelineComponent>(this, FName("TimelineAnimation"));
		MyTimeline->CreationMethod = EComponentCreationMethod::UserConstructionScript; // Indicate it comes from a blueprint so it gets cleared when we rerun construction scripts
		this->BlueprintCreatedComponents.Add(MyTimeline); // Add to array so it gets saved
		MyTimeline->SetNetAddressable();    // This component has a stable name that can be referenced for replication

		MyTimeline->SetPropertySetObject(this); // Set which object the timeline should drive properties on
		MyTimeline->SetDirectionPropertyName(FName("TimelineDirection"));

		MyTimeline->SetLooping(false);
		MyTimeline->SetTimelineLength(5.f);
		MyTimeline->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame);

		MyTimeline->SetPlaybackPosition(0.0f, false);

		//Add the float curve to the timeline and connect it to your timelines's interpolation function
		onTimelineCallback.BindUFunction(this, FName{ TEXT("TimelineCallback") });
		onTimelineFinishedCallback.BindUFunction(this, FName{ TEXT("TimelineFinishedCallback") });
		MyTimeline->AddInterpFloat(FloatCurve, onTimelineCallback);
		MyTimeline->SetTimelineFinishedFunc(onTimelineFinishedCallback);

		MyTimeline->RegisterComponent();
	}

	m_PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!m_PlayerController || !m_PlayerController->IsValidLowLevel())
	{
		return;
	}

	for (auto& Anim : m_PlayerAnimations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}


	for (auto& Anim : m_PlayerCombatAnimations)
	{
		GetAnimationInstance()->AddAnimMontage(static_cast<int>(Anim.Key), Anim.Value);
	}

	m_PlayerInfo = GetWorld()->GetGameInstance<UURGameInstance>()->GetPlayerData(FName(TEXT("Player2")));

	SetDefaultData();
}

void AWarriorCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyTimeline != NULL)
	{
		MyTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

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

	CombatTick(DeltaTime);
	CoolTimeTick(DeltaTime);
}

void AWarriorCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MouseMoveX"), this, &AWarriorCharacter::MouseMoveX);
	PlayerInputComponent->BindAxis(TEXT("MouseMoveY"), this, &AWarriorCharacter::MouseMoveY);

	PlayerInputComponent->BindAxis(FName(TEXT("LeftMove")), this, &AWarriorCharacter::PlayerLeftMove);
	PlayerInputComponent->BindAxis(FName(TEXT("RightMove")), this, &AWarriorCharacter::PlayerRightMove);
	PlayerInputComponent->BindAxis(FName(TEXT("ForwardMove")), this, &AWarriorCharacter::PlayerForwardMove);
	PlayerInputComponent->BindAxis(FName(TEXT("BackwardMove")), this, &AWarriorCharacter::PlayerBackwardMove);
	PlayerInputComponent->BindAction(FName(TEXT("ForwardMove")), EInputEvent::IE_Released, this, &AWarriorCharacter::ForwardKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("LeftMove")), EInputEvent::IE_Released, this, &AWarriorCharacter::LeftKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("RightMove")), EInputEvent::IE_Released, this, &AWarriorCharacter::RightKeyEnd);
	PlayerInputComponent->BindAction(FName(TEXT("BackwardMove")), EInputEvent::IE_Released, this, &AWarriorCharacter::BackwardKeyEnd);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction(FName(TEXT("AttackClick")), EInputEvent::IE_Pressed, this, &AWarriorCharacter::LeftAttack);
	PlayerInputComponent->BindAction(FName(TEXT("AttackClick")), EInputEvent::IE_Released, this, &AWarriorCharacter::LeftAttackUp);
	PlayerInputComponent->BindAction(FName(TEXT("SkillQ")), EInputEvent::IE_Pressed, this, &AWarriorCharacter::SkillQ);
	PlayerInputComponent->BindAction(FName(TEXT("SkillE")), EInputEvent::IE_Pressed, this, &AWarriorCharacter::SkillE);
	PlayerInputComponent->BindAction(FName(TEXT("SkillR")), EInputEvent::IE_Pressed, this, &AWarriorCharacter::SkillR);

	PlayerInputComponent->BindAction(FName(TEXT("CtrlKey")), EInputEvent::IE_Pressed, this, &AWarriorCharacter::CtrlKeyDown);
	PlayerInputComponent->BindAction(FName(TEXT("CtrlKey")), EInputEvent::IE_Released, this, &AWarriorCharacter::CtrlKeyOn);

	PlayerInputComponent->BindAction(FName(TEXT("ShiftKey")), EInputEvent::IE_Pressed, this, &AWarriorCharacter::ShiftKeyDown);
	PlayerInputComponent->BindAction(FName(TEXT("ShiftKey")), EInputEvent::IE_Released, this, &AWarriorCharacter::ShiftKeyOn);



	PlayerInputComponent->BindAxis(FName(TEXT("WheelAxis")), this, &AWarriorCharacter::WheelKey);


}

void AWarriorCharacter::CallDamage(double _Damage, AActor* _Actor)
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

void AWarriorCharacter::SetDefaultData()
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

void AWarriorCharacter::DashToJudge()
{
	/*if (m_IsForwardDown && !m_IsBackwardDown && !m_IsLeftDown && !m_IsRightDown)
	{
		FVector Location = GetActorLocation() + GetActorForwardVector() * m_DashDist;
		SetActorLocation(Location);
	}

	else if (m_IsBackwardDown && !m_IsForwardDown && !m_IsLeftDown && !m_IsRightDown)
	{
		FVector Location = GetActorLocation() - GetActorForwardVector() * m_DashDist;
		SetActorLocation(Location);
	}

	else if (m_IsLeftDown && !m_IsForwardDown && !m_IsBackwardDown && !m_IsRightDown)
	{
		FVector Location = GetActorLocation() - GetActorRightVector() * m_DashDist;
		SetActorLocation(Location);
	}

	else if (m_IsRightDown && !m_IsForwardDown && !m_IsLeftDown && !m_IsBackwardDown)
	{
		FVector Location = GetActorLocation() + GetActorRightVector() * m_DashDist;
		SetActorLocation(Location);
	}

	else if (m_IsForwardDown && m_IsLeftDown)
	{
		FVector Location = GetActorLocation() + (GetActorForwardVector() - GetActorRightVector()).GetSafeNormal() * m_DashDist;
		SetActorLocation(Location);
	}

	else if (m_IsForwardDown && m_IsRightDown)
	{
		FVector Location = GetActorLocation() + (GetActorForwardVector() + GetActorRightVector()).GetSafeNormal() * m_DashDist;
		SetActorLocation(Location);
	}

	else if (m_IsBackwardDown && m_IsLeftDown)
	{
		FVector Location = GetActorLocation() + (-GetActorForwardVector() - GetActorRightVector()).GetSafeNormal() * m_DashDist;
		SetActorLocation(Location);
	}

	else if (m_IsBackwardDown && m_IsRightDown)
	{
		FVector Location = GetActorLocation() + (-GetActorForwardVector() + GetActorRightVector()).GetSafeNormal() * m_DashDist;
		SetActorLocation(Location);
	}*/
	FVector InputVec = GetCharacterMovement()->GetLastInputVector();

	FHitResult HitResult;

	bool BlockingHit = false;
	bool InitialOverlap = false;
	float Time = 0.f;
	float Distance = 0.f;
	FVector Location;
	FVector ImpactPoint;
	FVector Normal;
	FVector ImpactNormal;
	UPhysicalMaterial* PhysMat = nullptr;
	AActor* HitActor = nullptr;
	UPrimitiveComponent* HitComponent = nullptr;
	FName HitBoneName;
	FName BoneName;
	int32 HitItem;
	int32 ElementIndex;
	int32 FaceIndex;
	FVector TraceStart;
	FVector TraceEnd;

	if (UAIBlueprintHelperLibrary::IsValidAIDirection(InputVec))
	{
		FVector EndVec = InputVec * 500.f + GetActorLocation();


		if (GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), EndVec, ECollisionChannel::ECC_Visibility))
		{
			UGameplayStatics::BreakHitResult(HitResult, BlockingHit, InitialOverlap, Time, Distance, Location,
				ImpactPoint, Normal, ImpactNormal, PhysMat, HitActor, HitComponent, HitBoneName, BoneName, HitItem,
				ElementIndex, FaceIndex, TraceStart, TraceEnd);

			DashFunc((InputVec * 800.f) + Location, InputVec);
		}
		else
		{
			UGameplayStatics::BreakHitResult(HitResult, BlockingHit, InitialOverlap, Time, Distance, Location,
				ImpactPoint, Normal, ImpactNormal, PhysMat, HitActor, HitComponent, HitBoneName, BoneName, HitItem,
				ElementIndex, FaceIndex, TraceStart, TraceEnd);

			DashFunc(TraceEnd, InputVec);
		}
	}
	else
	{
		FVector EndVec = GetActorForwardVector() * 500.f + GetActorLocation();
			
		if (GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), EndVec, ECollisionChannel::ECC_Visibility))
		{
			UGameplayStatics::BreakHitResult(HitResult, BlockingHit, InitialOverlap, Time, Distance, Location,
				ImpactPoint, Normal, ImpactNormal, PhysMat, HitActor, HitComponent, HitBoneName, BoneName, HitItem,
				ElementIndex, FaceIndex, TraceStart, TraceEnd);

			DashFunc((GetActorForwardVector() * -55.f) + Location, GetActorForwardVector());
		}
		else
		{
			UGameplayStatics::BreakHitResult(HitResult, BlockingHit, InitialOverlap, Time, Distance, Location,
				ImpactPoint, Normal, ImpactNormal, PhysMat, HitActor, HitComponent, HitBoneName, BoneName, HitItem,
				ElementIndex, FaceIndex, TraceStart, TraceEnd);

			DashFunc(TraceEnd, GetActorForwardVector());
		}
	}
}

void AWarriorCharacter::CombatTick(float DeltaTime)
{
	if (m_IsCombating)
	{
		m_CombatTime -= DeltaTime;

		if (m_CombatTime <= 0.f)
		{
			m_CombatTime = 7.f;

			m_IsCombating = false;

			UAnimMontage* FindMontage = GetAnimationInstance()->GetAnimation(WarriorCombatAnimation::CombatIdle);

			if (GetAnimationInstance()->Montage_IsPlaying(FindMontage))
			{
				GetAnimationInstance()->ChangeAnimMontage(DefaultAnimation::Idle);
			}
		}
	}
}

void AWarriorCharacter::CoolTimeTick(float DeltaTime)
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

bool AWarriorCharacter::JudgeFunc()
{
	if (GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashLeft) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashRight) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashForward) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashBackward) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashForwardLeft) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashForwardRight) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashBackwardLeft) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashBackwardRight) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::Combo1) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::Combo2) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::Combo3) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::Combo4) ||
		GetAnimationInstance()->IsAnimMontage(DefaultAnimation::Attack))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AWarriorCharacter::DashJudgeFunc()
{
	if (GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashLeft) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashRight) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashForward) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashBackward) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashForwardLeft) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashForwardRight) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashBackwardLeft) ||
		GetAnimationInstance()->IsAnimMontage(WarriorAnimation::DashBackwardRight))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AWarriorCharacter::DashFunc(const FVector& DashDir, const FVector& DashVelocity)
{
	m_DashDir = DashDir;
	m_DashVelocity = DashVelocity;
	PlayTimeline();
}

void AWarriorCharacter::TimelineCallback(float val)
{
	FVector NewLocation = UKismetMathLibrary::VLerp(GetActorLocation(), m_DashDir, val);

	SetActorLocation(NewLocation);
}

void AWarriorCharacter::TimelineFinishedCallback()
{
	GetCharacterMovement()->Velocity = m_DashVelocity * 500.f;
}

void AWarriorCharacter::PlayTimeline()
{
	if (MyTimeline != NULL)
	{
		MyTimeline->PlayFromStart();
	}
}
