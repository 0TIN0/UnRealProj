// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Animation/AnimNotify/UR_FootStepSoundNotify.h"
#include "../../WarriorCharacter.h"
#include "Components/AudioComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Hearing.h"


UUR_FootStepSoundNotify::UUR_FootStepSoundNotify()
{
}

void UUR_FootStepSoundNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	AWarriorCharacter* Character = MeshComp->GetOwner<AWarriorCharacter>();

	if (!Character || !Character->IsValidLowLevel())
	{
		return;
	}

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(Character);
	CollisionParams.bReturnPhysicalMaterial = true;
	
	FVector StartPos = MeshComp->GetOwner()->GetActorLocation();
	FVector EndPos = StartPos;
	EndPos.Z -= 500.f;

	double Length = Character->GetVelocity().Length();

	// �޸��� or �ȱ� �ӵ��� ���� �߼Ҹ� ������ ����
	double OutValue = UKismetMathLibrary::MapRangeClamped(Length, 0.0, 1000.0, 0.0, 1.0);

	double StepSoundM = 1.0;

	OutValue *= StepSoundM;

	FHitResult HitResult;
	
	// �ٴ����� Lay�� �� ������ ���׸����� �Ǵ��� �ش� Step Sound�� ����ϵ��� ����
	if (Character->GetWorld()->LineTraceSingleByChannel(HitResult, StartPos, EndPos, ECollisionChannel::ECC_Visibility, CollisionParams))
	{
		USoundBase* Sound = nullptr;

		m_StepSurface = UGameplayStatics::GetSurfaceType(HitResult);

		SelectSoundBase(&Sound);
		
		UAudioComponent* AudioComp = UGameplayStatics::SpawnSoundAttached(Sound, MeshComp, FName(TEXT("None")), FVector(), EAttachLocation::Type::KeepRelativeOffset,
			false, OutValue, OutValue);

		UAISense_Hearing::ReportNoiseEvent(Character->GetWorld(), HitResult.Location, StepSoundM, nullptr, 0.f, FName(TEXT("Detected")));
	}
	else
	{
		return;
	}

}

void UUR_FootStepSoundNotify::SelectSoundBase(USoundBase** _SoundBase)
{
	switch (m_StepSurface) 
	{
	case SurfaceType_Default:
		break;
	case SurfaceType1:
		*_SoundBase = m_Dirty;
		break;
	case SurfaceType2:
		*_SoundBase = m_Modern;
		break;
	case SurfaceType3:
		break;
	case SurfaceType4:
		break;
	}
}
