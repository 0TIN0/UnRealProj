// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Play/Skill/URProjectile.h"
#include "UR_ArrowProjectile.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API AUR_ArrowProjectile : public AURProjectile
{
	GENERATED_BODY()

public:
	AUR_ArrowProjectile();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* m_ArrowComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UNiagaraComponent* m_ArrowTrail;

	class UNiagaraSystem* m_NiagaraFX;

	class AURCharacter* m_Player;

	float m_InterpSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
		virtual	void OnCollision(UPrimitiveComponent* _Component, AActor* _DestActor, UPrimitiveComponent* _DestComponent,
			int32 _OtherBodyIndex, bool _FromSweep, const FHitResult& _Result) override;
	
};
