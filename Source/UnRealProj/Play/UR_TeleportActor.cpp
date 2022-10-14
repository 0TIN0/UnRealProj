// Fill out your copyright notice in the Description page of Project Settings.


#include "Play/UR_TeleportActor.h"

// Sets default values
AUR_TeleportActor::AUR_TeleportActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AUR_TeleportActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUR_TeleportActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

