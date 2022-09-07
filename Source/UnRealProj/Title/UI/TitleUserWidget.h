// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TitleUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALPROJ_API UTitleUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable, Category = UR)
	void TitleStartEvent();
};
