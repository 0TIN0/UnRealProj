// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../../URCharacter.h"
#include "UR_BlackHole.generated.h"

UCLASS()
class UNREALPROJ_API AUR_BlackHole : public AURCharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUR_BlackHole();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		class UNiagaraComponent* m_BlackHole;

	class UNiagaraSystem* m_NiagaraFX;

	class AWarriorCharacter* m_Player;

	USoundBase* m_SpawnSound;

	float m_PullDist;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

};
