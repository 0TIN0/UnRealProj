// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Object/Door/UR_DoorActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AUR_DoorActor::AUR_DoorActor()	:
	m_MoveTime(5.f)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	{

		ConstructorHelpers::FObjectFinder<UStaticMesh> MeshPath(TEXT("StaticMesh'/Game/Resource/Play/Map/ResearchMegaPack/ResearchCenter/Meshes/SM_Door_2.SM_Door_2'"));
		m_DoorComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("Door")));
		m_DoorComponent->SetRelativeScale3D(FVector(1.64, 2.0, 1.93));
		m_DoorComponent->SetRelativeRotation(FRotator(0.0, 90.0, 0.0));
		RootComponent = m_DoorComponent;

		if (MeshPath.Object && MeshPath.Object->IsValidLowLevel())
		{
			m_DoorComponent->SetStaticMesh(MeshPath.Object);
		}
	}

	{

		m_TriggerCollision = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("DoorTrigger")));
		m_TriggerCollision->SetRelativeScale3D(FVector(25.0, 10.0, 10.0));
		m_TriggerCollision->SetBoxExtent(FVector(25.0, 10.0, 10.0));
		m_TriggerCollision->SetupAttachment(m_DoorComponent);
		m_TriggerCollision->SetCollisionProfileName(FName(TEXT("Trigger")));
		m_TriggerCollision->SetRelativeLocation(FVector(-500.0, 300.0, 100.0));

		//m_TriggerCollision->Collision
	}
}

// Called when the game starts or when spawned
void AUR_DoorActor::BeginPlay()
{
	Super::BeginPlay();

	m_TriggerCollision->OnComponentBeginOverlap.AddDynamic(this, &AUR_DoorActor::TriggerBeginOverlap);
	
}

// Called every frame
void AUR_DoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_Enable)
	{
		m_MoveTime -= DeltaTime;

		if (m_MoveTime >= 0.f)
		{
			SetActorLocation(GetActorLocation() + FVector(0.0, -3.0, 0.0));
		}
		else
			m_Enable = false;
	}

}

void AUR_DoorActor::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	m_Enable = true;
}

