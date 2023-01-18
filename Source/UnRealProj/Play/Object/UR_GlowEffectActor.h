// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UR_GlowEffectActor.generated.h"

UCLASS()
class UNREALPROJ_API AUR_GlowEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUR_GlowEffectActor();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* m_MeshComp;

	class AURCharacter* m_Player;
	class APlayerCameraManager* m_PlayerCamera;

	float m_Time;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

};
