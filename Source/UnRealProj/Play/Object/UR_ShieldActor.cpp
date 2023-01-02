// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/Object/UR_ShieldActor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
AUR_ShieldActor::AUR_ShieldActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Parameters can be set like this (see documentation for further info) - the names and type must match the user exposed parameter in the Niagara System
	m_Shield = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), m_NiagaraFX, GetActorLocation());
}

// Called when the game starts or when spawned
void AUR_ShieldActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_ShieldActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

