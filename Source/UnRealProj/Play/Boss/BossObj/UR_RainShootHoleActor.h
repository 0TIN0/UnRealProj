// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UR_RainShootHoleActor.generated.h"

UCLASS()
class UNREALPROJ_API AUR_RainShootHoleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUR_RainShootHoleActor();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* m_HoleComponent;

	class UParticleSystem* m_FastHoleFX;
	class UParticleSystem* m_NormalHoleFX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* m_MeteorComponent;
	class UParticleSystem* m_MeteorFX;

	class USoundBase* m_SpawnSound;

	float m_DestroyTime;

	bool m_ChangeFXEnable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

};
