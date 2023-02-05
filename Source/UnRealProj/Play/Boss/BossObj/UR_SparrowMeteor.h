// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/Skill/URProjectile.h"
#include "UR_SparrowMeteor.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AUR_SparrowMeteor : public AURProjectile
{
	GENERATED_BODY()

public:
	AUR_SparrowMeteor();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UParticleSystemComponent* m_MeteorComponent;


	class UParticleSystem* m_MeteorFX;

	class UParticleSystem* m_HitParticleFX;


	bool m_HitEnable;
	float m_DestroyTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
		virtual	void OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent,
			int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result) override;
	
};
